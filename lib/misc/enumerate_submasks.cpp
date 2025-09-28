// Enumerate all submasks of mask in 2^(active bits of mask), which is optimal
// in DECREASING order
for (i64 submask = mask; submask > 0; submask = (submask - 1) & mask){
    // do stuff
}
// NOTE: needs to treat 0 submask separately
