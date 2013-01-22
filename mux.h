#ifndef __MUX_H
#define __MUX_H

#include <iostream>

#include "bvec-basic.h"

namespace chdl {
  // Ordinary 2-input N-bit mux
  template <unsigned N> bvec<N> Mux(node sel, bvec<N> i0, bvec<N> i1) {
    bvec<N> o;
    for (unsigned i = 0; i < N; ++i)
      o[i] = Or(And(Inv(sel), i0[i]), And(sel, i1[i]));
    return o;
  }

  // 2^M-input N-bit mux
  template <unsigned N, unsigned M>
    bvec<N> Mux(bvec<M> sel, vec<1<<M, bvec<N>> inputs)
  {
    vec<(2<<M), bvec<N>> nodes;
    nodes[range<(1<<M),2*(1<<M)-1>()] = inputs;
    for (int i = (1<<M)-1; i >= 1; --i)
      nodes[i] = Mux(sel[M - log2(i) - 1], nodes[i*2], nodes[i*2+1]);
    return nodes[1];
  }

  // 1-2 decoder/demux
  bvec<2> Decoder(node i, node e) {
    bvec<2> out;
    out[0] = And(Inv(i), e);
    out[1] = And(i, e);
    return out;
  }

  // M-2^M decoder/demux
  template <unsigned M> bvec<(1<<M)> Decoder(bvec<M> sel, node e) {
    bvec<2*(1<<M)> nodes;
    nodes[1] = e;
    for (unsigned i = 1; i < (1<<M); ++i) {
      bvec<2> r = Decoder(sel[M - log2(i) - 1], nodes[i]);
      nodes[2*i] = r[0];
      nodes[2*i+1] = r[1];
    }
    return nodes[range<(1<<M),2*(1<<M)-1>()];
  }
};

#endif