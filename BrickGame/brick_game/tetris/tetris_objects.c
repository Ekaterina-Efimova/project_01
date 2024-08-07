#include "tetris_objects.h"

void tetraminoes(int tetramino, int state, int tetr[4][2]) {
  int tetraminoes_states[7][4][4][2] = {
      {{{3, 0}, {4, 0}, {5, 0}, {6, 0}},  // ▣▣▣▣
       {{3, 0}, {3, 1}, {3, 2}, {3, 3}},
       {{3, 0}, {4, 0}, {5, 0}, {6, 0}},
       {{3, 0}, {3, 1}, {3, 2}, {3, 3}}},

      {{{3, 0}, {4, 0}, {5, 0}, {5, 1}},  // ▣▣▣
       {{4, 0}, {4, 1}, {4, 2}, {3, 2}},  //   ▣
       {{3, 0}, {3, 1}, {4, 1}, {5, 1}},
       {{4, 0}, {3, 0}, {3, 1}, {3, 2}}},

      {{{4, 1}, {4, 0}, {5, 0}, {6, 0}},  // ▣▣▣
       {{5, 0}, {6, 0}, {6, 1}, {6, 2}},  // ▣
       {{6, 0}, {6, 1}, {5, 1}, {4, 1}},
       {{4, 0}, {4, 1}, {4, 2}, {5, 2}}},

      {{{4, 0}, {5, 0}, {4, 1}, {5, 1}},  // ▣▣
       {{4, 0}, {5, 0}, {4, 1}, {5, 1}},  // ▣▣
       {{4, 0}, {5, 0}, {4, 1}, {5, 1}},
       {{4, 0}, {5, 0}, {4, 1}, {5, 1}}},

      {{{4, 0}, {5, 0}, {3, 1}, {4, 1}},  //   ▣▣
       {{3, 0}, {3, 1}, {4, 1}, {4, 2}},  // ▣▣
       {{4, 0}, {5, 0}, {3, 1}, {4, 1}},
       {{3, 0}, {3, 1}, {4, 1}, {4, 2}}},

      {{{3, 0}, {4, 0}, {4, 1}, {5, 1}},  // ▣▣
       {{5, 0}, {4, 1}, {5, 1}, {4, 2}},  //  ▣▣
       {{3, 0}, {4, 0}, {4, 1}, {5, 1}},
       {{5, 0}, {4, 1}, {5, 1}, {4, 2}}},

      {{{3, 0}, {4, 0}, {5, 0}, {4, 1}},  // ▣▣▣
       {{4, 0}, {3, 1}, {4, 1}, {4, 2}},  //  ▣
       {{4, 0}, {3, 1}, {4, 1}, {5, 1}},
       {{4, 1}, {4, 2}, {4, 0}, {5, 1}}}};

  for (int i = 0; i < 4; i++) {
    tetr[i][0] = tetraminoes_states[tetramino][state][i][0];
    tetr[i][1] = tetraminoes_states[tetramino][state][i][1];
  }
}
