static const uint16_t therm_table[] =
{
   1010, // [ 0] C=-40 R=253903
   1009, // [ 1] C=-39 R=238312
   1008, // [ 2] C=-38 R=223800
   1007, // [ 3] C=-37 R=210283
   1006, // [ 4] C=-36 R=197687
   1005, // [ 5] C=-35 R=185941
   1004, // [ 6] C=-34 R=174984
   1003, // [ 7] C=-33 R=164755
   1002, // [ 8] C=-32 R=155202
   1000, // [ 9] C=-31 R=146274
    999, // [10] C=-30 R=137928
    998, // [11] C=-29 R=130121
    996, // [12] C=-28 R=122813
    995, // [13] C=-27 R=115971
    993, // [14] C=-26 R=109561
    991, // [15] C=-25 R=103552
    990, // [16] C=-24 R=97918
    988, // [17] C=-23 R=92631
    986, // [18] C=-22 R=87669
    984, // [19] C=-21 R=83008
    982, // [20] C=-20 R=78630
    980, // [21] C=-19 R=74514
    977, // [22] C=-18 R=70643
    975, // [23] C=-17 R=67002
    973, // [24] C=-16 R=63574
    970, // [25] C=-15 R=60346
    967, // [26] C=-14 R=57305
    965, // [27] C=-13 R=54439
    962, // [28] C=-12 R=51737
    959, // [29] C=-11 R=49188
    956, // [30] C=-10 R=46782
    952, // [31] C=-9 R=44511
    949, // [32] C=-8 R=42367
    946, // [33] C=-7 R=40340
    942, // [34] C=-6 R=38425
    938, // [35] C=-5 R=36613
    935, // [36] C=-4 R=34900
    931, // [37] C=-3 R=33279
    927, // [38] C=-2 R=31744
    922, // [39] C=-1 R=30290
    918, // [40] C= 0 R=28913
    914, // [41] C= 1 R=27608
    909, // [42] C= 2 R=26371
    905, // [43] C= 3 R=25197
    900, // [44] C= 4 R=24084
    895, // [45] C= 5 R=23027
    890, // [46] C= 6 R=22024
    884, // [47] C= 7 R=21071
    879, // [48] C= 8 R=20166
    874, // [49] C= 9 R=19306
    868, // [50] C=10 R=18488
    862, // [51] C=11 R=17710
    856, // [52] C=12 R=16970
    850, // [53] C=13 R=16265
    844, // [54] C=14 R=15595
    838, // [55] C=15 R=14957
    832, // [56] C=16 R=14348
    825, // [57] C=17 R=13769
    819, // [58] C=18 R=13217
    812, // [59] C=19 R=12690
    805, // [60] C=20 R=12188
    798, // [61] C=21 R=11709
    791, // [62] C=22 R=11251
    784, // [63] C=23 R=10815
    777, // [64] C=24 R=10398
    769, // [65] C=25 R=10000
    762, // [66] C=26 R=9620
    754, // [67] C=27 R=9256
    746, // [68] C=28 R=8909
    739, // [69] C=29 R=8576
    731, // [70] C=30 R=8259
    723, // [71] C=31 R=7955
    715, // [72] C=32 R=7664
    707, // [73] C=33 R=7385
    699, // [74] C=34 R=7118
    691, // [75] C=35 R=6863
    683, // [76] C=36 R=6618
    674, // [77] C=37 R=6384
    666, // [78] C=38 R=6159
    658, // [79] C=39 R=5944
    649, // [80] C=40 R=5737
    641, // [81] C=41 R=5539
    633, // [82] C=42 R=5349
    624, // [83] C=43 R=5166
    616, // [84] C=44 R=4991
    607, // [85] C=45 R=4823
    599, // [86] C=46 R=4662
    591, // [87] C=47 R=4506
    582, // [88] C=48 R=4357
    574, // [89] C=49 R=4214
    565, // [90] C=50 R=4076
    557, // [91] C=51 R=3944
    549, // [92] C=52 R=3817
    540, // [93] C=53 R=3694
    532, // [94] C=54 R=3576
    524, // [95] C=55 R=3463
    516, // [96] C=56 R=3354
    508, // [97] C=57 R=3249
    499, // [98] C=58 R=3148
    491, // [99] C=59 R=3050
    483, // [100] C=60 R=2956
    476, // [101] C=61 R=2866
    468, // [102] C=62 R=2779
    460, // [103] C=63 R=2695
    452, // [104] C=64 R=2614
    445, // [105] C=65 R=2536
    437, // [106] C=66 R=2461
    429, // [107] C=67 R=2388
    422, // [108] C=68 R=2318
    415, // [109] C=69 R=2250
    407, // [110] C=70 R=2185
    400, // [111] C=71 R=2122
    393, // [112] C=72 R=2061
    386, // [113] C=73 R=2002
    379, // [114] C=74 R=1945
    373, // [115] C=75 R=1890
    366, // [116] C=76 R=1837
    359, // [117] C=77 R=1786
    353, // [118] C=78 R=1737
    346, // [119] C=79 R=1689
    340, // [120] C=80 R=1642
    334, // [121] C=81 R=1598
    328, // [122] C=82 R=1554
    321, // [123] C=83 R=1512
    316, // [124] C=84 R=1472
    310, // [125] C=85 R=1433
    304, // [126] C=86 R=1395
    298, // [127] C=87 R=1358
    293, // [128] C=88 R=1322
    287, // [129] C=89 R=1288
    282, // [130] C=90 R=1254
    276, // [131] C=91 R=1222
    271, // [132] C=92 R=1191
    266, // [133] C=93 R=1160
    261, // [134] C=94 R=1131
    256, // [135] C=95 R=1102
    251, // [136] C=96 R=1074
    246, // [137] C=97 R=1048
    242, // [138] C=98 R=1022
    237, // [139] C=99 R=996
    233, // [140] C=100 R=972
    228, // [141] C=101 R=948
    224, // [142] C=102 R=925
    220, // [143] C=103 R=903
    216, // [144] C=104 R=881
    211, // [145] C=105 R=860
    207, // [146] C=106 R=839
    203, // [147] C=107 R=819
    200, // [148] C=108 R=800
    196, // [149] C=109 R=781
    192, // [150] C=110 R=763
    188, // [151] C=111 R=745
    185, // [152] C=112 R=728
    181, // [153] C=113 R=711
    178, // [154] C=114 R=695
    175, // [155] C=115 R=679
    171, // [156] C=116 R=664
    168, // [157] C=117 R=649
    165, // [158] C=118 R=634
    162, // [159] C=119 R=620
    159, // [160] C=120 R=607
    156, // [161] C=121 R=593
    153, // [162] C=122 R=580
    150, // [163] C=123 R=567
    147, // [164] C=124 R=555
    145, // [165] C=125 R=543
};

#define T_AT_IDX(idx) (-40 + ((idx) * 1))
#define T_STEP (1)
#define T_LAST_IDX (165)

