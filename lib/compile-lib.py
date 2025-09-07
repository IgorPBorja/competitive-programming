#!/usr/bin/env python3
import os
import argparse

from pathlib import Path

LIB_DIR = Path('.')
TEX_DIR = Path('./tex')
HEADER = r"""
\documentclass[11pt, a4paper, twoside]{article}   % two-column layout
\usepackage[utf8]{inputenc}
\usepackage[landscape, left=0.5cm, right=0.5cm, top=1cm, bottom=1.5cm]{geometry}
\usepackage{hyperref}
\usepackage{titlesec}
\usepackage{verbatim}
\usepackage{listings}
\usepackage{color}   % for coloring the code
\titleformat{\section}{\normalfont\Large\bfseries}{\thesection}{1em}{}
\titleformat{\subsection}{\normalfont\large\bfseries}{\thesubsection}{1em}{}
\setlength{\columnseprule}{0.2pt} %barra separando as duas colunas
\setlength{\columnsep}{10pt} %distancia do texto ate a barra
"""

# see https://github.com/brunomaletta/Biblioteca/blob/master/latex/comeco.tex
LISTING_OPTIONS = r"""
\definecolor{gray}{rgb}{0.4, 0.4, 0.4} %cor pros comentarios
%\renewcommand{\footnotesize}{\small} %isso eh pra mudar o tamanho da fonte do codigo
\lstset{
breaklines=true,
keywordstyle=\color{blue}\bfseries,
commentstyle=\color{gray},
breakatwhitespace=true,
language=C++,
%frame=single,
numbers=none,
rulecolor=\color{black},
showstringspaces=false
stringstyle=\color{blue},
tabsize=4,
basicstyle=\ttfamily\footnotesize, % font
}
\lstset{literate=
%   *{0}{{{\color{red!20!violet}0}}}1
%    {1}{{{\color{red!20!violet}1}}}1
%    {2}{{{\color{red!20!violet}2}}}1
%    {3}{{{\color{red!20!violet}3}}}1
%    {4}{{{\color{red!20!violet}4}}}1
%    {5}{{{\color{red!20!violet}5}}}1
%    {6}{{{\color{red!20!violet}6}}}1
%    {7}{{{\color{red!20!violet}7}}}1
%    {8}{{{\color{red!20!violet}8}}}1
%    {9}{{{\color{red!20!violet}9}}}1
%	 {l}{$\text{l}$}1
	{~}{$\sim$}{1}
}
"""

# Recursively find all code files under lib/
def find_code_files(base_dir):
    code_files = []
    for root, dirs, files in os.walk(base_dir):
        for file in files:
            if file.endswith(('.cpp', '.hpp')):
                code_files.append(Path(root) / file)
    return sorted(code_files)

# Recursively find all documentation files under lib/
def find_doc_files(base_dir):
    doc_files = []
    for root, dirs, files in os.walk(base_dir):
        for file in files:
            if file.endswith('.tex') or file.endswith('.md'):
                doc_files.append(Path(root) / file)
    return sorted(doc_files)

# def make_tex_filename(code_path):
#     # Replace / with _ and . with _ for unique tex file names
#     return Path(TEX_DIR) / ('lib_snippets_' + str(code_path).replace('/', '_').replace('.', '_') + '.tex')

# def write_code_tex(code_path, tex_path):
#     with open(code_path, 'r') as f:
#         code = f.read()
#     with open(tex_path, 'w') as f:
#         f.write('% Auto-generated from {}\n'.format(code_path))
#         f.write('\\begin{verbatim}\n')
#         f.write(code)
#         f.write('\n\\end{verbatim}\n')

def cleanup():
    # Clean up auxiliary files
    if os.path.exists(Path(TEX_DIR) / "main.pdf"):
        os.rename(Path(TEX_DIR) / "main.pdf", Path(LIB_DIR) / "main.pdf")
    for filepath in os.listdir(TEX_DIR):
        os.remove(Path(TEX_DIR) / filepath)
    os.rmdir(Path(TEX_DIR))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--debug", action="store_true", help="If active, keep .tex file after compilation")
    args = parser.parse_args()

    if os.path.exists(Path(LIB_DIR) / "main.pdf"):
        os.remove(Path(LIB_DIR) / "main.pdf")
    os.makedirs(TEX_DIR, exist_ok=True)
    code_files = find_code_files(LIB_DIR)
    doc_files = find_doc_files(LIB_DIR)
    
    def escape_fname(fname: str) -> str:
        return fname.replace('-', '_').replace('_', '\\_')
    
    def escape_section_name(section_name: str):
        return " ".join(section_name.split("_")).title()

    sections = set()
    with open(Path(TEX_DIR) / 'main.tex', 'w') as f:
        print(HEADER, file=f)
        print(LISTING_OPTIONS, file=f)
        print(r"\title{ICPC Lib}", file=f)
        print(r"\begin{document}", file=f)
        print(r"\twocolumn", file=f)
        print(r"\date{\today}", file=f)
        print(r"\maketitle", file=f)
        print(r"\tableofcontents", file=f)


        for doc_path in doc_files:
            doc_path = doc_path.relative_to(LIB_DIR)
            with open(doc_path, 'r') as doc_file:
                doc_content = doc_file.read()
            # If it's a markdown file, we can convert it to LaTeX using pandoc
            if doc_path.suffix == '.md':
                import subprocess
                result = subprocess.run(['pandoc', '-f', 'markdown', '-t', 'latex'], input=doc_content.encode('utf-8'), capture_output=True)
                if result.returncode != 0:
                    print(f"Error converting {doc_path} to LaTeX: {result.stderr.decode('utf-8')}")
                    raise ValueError(f"Error converting {doc_path} to LaTeX")
                doc_content = result.stdout.decode('utf-8')
            f.write(doc_content + '\n')

        for code_path in code_files:
            code_path = code_path.relative_to(LIB_DIR)
            include_path = Path("..") / code_path   # compilation happens inside of TEX_DIR
            snippet_name = escape_fname(str(os.path.basename(code_path)))
            if len(code_path.parts) >= 3:
                raise ValueError(f"Nesting level should be at most 2, found {len(code_path.parts)} at path={code_path}")
            elif len(code_path.parts) == 2:
                section_name = escape_section_name(str(code_path.parts[0]))
                if section_name not in sections:
                    f.write(f'\\section{{{section_name}}}\n')
                    sections.add(section_name)
                f.write(f'\\subsection{{{snippet_name}}}\n')
            else:
                f.write(f'\\section{{{snippet_name}}}\n')
            f.write(f'\\lstinputlisting{{{include_path}}}\n')

        f.write("\n\\end{document}\n")

    # Compile twice to generate TOC correctly
    os.system(f'cd {TEX_DIR} && echo "Running on $(pwd)" && pdflatex main.tex')
    os.system(f'cd {TEX_DIR} && echo "Running (second compilation for ToC) on $(pwd)" && pdflatex main.tex')
    if not args.debug:
        cleanup()


if __name__ == '__main__':
    main()
