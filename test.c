#include <stdio.h>

#define ROW_CNT (1024)
//#define ROW_CNT (512)
#define OCT_CNT (80)
#define DBG(x) 

#define SCRAMBLE(VRA, COEFF) (((VRA)*(COEFF))%ROW_CNT)

typedef unsigned int ROW_ADDR_t;

unsigned int coeffs[] = {  1,   3,   5,  15,   7,  21,  11,  33,  // chip0
                          13,  39,  17,  51,  19,  57,  23,  69,  // chip1
                          25,  75,  27,  81,  29,  87,  31,  93,  // chip2
                          35, 105,  37, 111,  41, 123,  43, 129,  // chip3
                          45, 135,  47, 141,  49, 147,  53, 159,  // chip4
                          55, 165,  59, 177,  61, 183,  63, 189,  // chip5
                          65, 195,  67, 201,  71, 213,  73, 219,  // chip6
                          77, 231,  79, 237,  83, 249,  85, 255,  // chip7
                          89, 267,  91, 273,  95, 285,  97, 291,  // chip8
                         101, 303, 103, 309, 107, 321, 109, 327}; // chip9

// inverse coefficients
unsigned int incoeffs[] = {  1,   3,   5,  15,   7,  21,  11,  33,  // chip0
                            13,  39,  17,  51,  19,  57,  23,  69,  // chip1
                            25,  75,  27,  81,  29,  87,  31,  93,  // chip2
                            35, 105,  37, 111,  41, 123,  43, 129,  // chip3
                            45, 135,  47, 141,  49, 147,  53, 159,  // chip4
                            55, 165,  59, 177,  61, 183,  63, 189,  // chip5
                            65, 195,  67, 201,  71, 213,  73, 219,  // chip6
                            77, 231,  79, 237,  83, 249,  85, 255,  // chip7
                            89, 267,  91, 273,  95, 285,  97, 291,  // chip8
                           101, 303, 103, 309, 107, 321, 109, 327}; // chip9


ROW_ADDR_t a0_VRA;
ROW_ADDR_t a0_PRAs[OCT_CNT];

ROW_ADDR_t v0_0_PRAs[OCT_CNT];
ROW_ADDR_t v0_1_PRAs[OCT_CNT];

ROW_ADDR_t a1_VRA;
ROW_ADDR_t a1_PRAs[OCT_CNT];

ROW_ADDR_t v1_0_PRAs[OCT_CNT];
ROW_ADDR_t v1_1_PRAs[OCT_CNT];

ROW_ADDR_t a2_VRA;
ROW_ADDR_t a2_PRAs[OCT_CNT];

ROW_ADDR_t v2_0_PRAs[OCT_CNT];
ROW_ADDR_t v2_1_PRAs[OCT_CNT];

ROW_ADDR_t a3_VRA;
ROW_ADDR_t a3_PRAs[OCT_CNT];

ROW_ADDR_t v3_0_PRAs[OCT_CNT];
ROW_ADDR_t v3_1_PRAs[OCT_CNT];

void get_PRAs(ROW_ADDR_t vra, ROW_ADDR_t *pras)
{
    for (int i=0; i<OCT_CNT; i++) {
        pras[i] = SCRAMBLE(vra, coeffs[i]);
    }
}

void print_RAs(char *header, ROW_ADDR_t *ras)
{
    printf("%8s", header);
    for (int i=0; i<OCT_CNT; i++) {
        printf("%4d, ", ras[i]);
    }
    printf("\n");
}

int main()
{
    unsigned long long  conflict_cnt[16] = {0, };

    a0_VRA = 0;
    get_PRAs(a0_VRA, a0_PRAs);

    DBG(printf("Agg0:VRA %d\n", a0_VRA);)
    DBG(print_RAs("Agg0:PRAs", a0_PRAs);)

    for (int i=0; i<OCT_CNT; i++) {
        v0_0_PRAs[i] = (a0_PRAs[i]-1)%ROW_CNT;
        v0_1_PRAs[i] = (a0_PRAs[i]+1)%ROW_CNT;
    }
    DBG(print_RAs("V0-0:PRAs", v0_0_PRAs);)
    DBG(print_RAs("V0-1:PRAs", v0_1_PRAs);)

    for (ROW_ADDR_t a1_VRA = 0; (a1_VRA<ROW_CNT); a1_VRA++) {
        get_PRAs(a1_VRA, a1_PRAs);

        DBG(printf("Agg1:VRA %d\n", a1_VRA);)
        DBG(print_RAs("Agg1:PRAs", a1_PRAs);)
        for (int i=0; i<OCT_CNT; i++) {
            v1_0_PRAs[i] = (a1_PRAs[i]-1)%ROW_CNT;
            v1_1_PRAs[i] = (a1_PRAs[i]+1)%ROW_CNT;
        }
        DBG(print_RAs("V1-0:PRAs", v1_0_PRAs);)
        DBG(print_RAs("V1-1:PRAs", v1_1_PRAs);)

        for (ROW_ADDR_t a2_VRA = 0; (a2_VRA<ROW_CNT); a2_VRA++) {
            get_PRAs(a2_VRA, a2_PRAs);

            DBG(printf("Agg2:VRA %d\n", a2_VRA);)
            DBG(print_RAs("Agg2:PRAs", a2_PRAs);)
            for (int i=0; i<OCT_CNT; i++) {
                v2_0_PRAs[i] = (a2_PRAs[i]-1)%ROW_CNT;
                v2_1_PRAs[i] = (a2_PRAs[i]+1)%ROW_CNT;
            }
            DBG(print_RAs("V2-0:PRAs", v2_0_PRAs);)
            DBG(print_RAs("V2-1:PRAs", v2_1_PRAs);)

            for (ROW_ADDR_t a3_VRA = 0; (a3_VRA<ROW_CNT); a3_VRA++) {
                get_PRAs(a3_VRA, a3_PRAs);

                DBG(printf("Agg3:VRA %d\n", a3_VRA);)
                DBG(print_RAs("Agg3:PRAs", a3_PRAs);)
                for (int i=0; i<OCT_CNT; i++) {
                    v3_0_PRAs[i] = (a3_PRAs[i]-1)%ROW_CNT;
                    v3_1_PRAs[i] = (a3_PRAs[i]+1)%ROW_CNT;
                }
                DBG(print_RAs("V3-0:PRAs", v3_0_PRAs);)
                DBG(print_RAs("V3-1:PRAs", v3_1_PRAs);)

                // check
                for (int vra=0; vra<ROW_CNT; vra++) {
                    unsigned word_error_cnt = 0;
                    int error_locations[] = {-1, -1, -1, -1, -1, -1, -1};
                    for (int j=0; j<OCT_CNT; j++) {
                        ROW_ADDR_t  pra = SCRAMBLE(vra, coeffs[j]);
                        if (  (pra==v0_0_PRAs[j])
                            ||(pra==v0_1_PRAs[j])
                            ||(pra==v1_0_PRAs[j])
                            ||(pra==v1_1_PRAs[j])
                            ||(pra==v2_0_PRAs[j])
                            ||(pra==v2_1_PRAs[j])
                            ||(pra==v3_0_PRAs[j])
                            ||(pra==v3_1_PRAs[j])) { error_locations[word_error_cnt++] = j; }
                    }
                    conflict_cnt[word_error_cnt]++;
                    DBG(printf("Error count: %d\n", word_error_cnt);)
                /*
                if (word_error_cnt>2) {
                    printf("Why?\n");
                    printf("Error VRA: %d\n", vra);
                    printf("%d %d %d %d %d\n",
                                    error_locations[0],
                                    error_locations[1],
                                    error_locations[2],
                                    error_locations[3],
                                    error_locations[4]);
                    printf("%d %d %d %d %d\n",
                                    (error_locations[0]>=0) ? coeffs[error_locations[0]] : -1,
                                    (error_locations[1]>=0) ? coeffs[error_locations[1]] : -1,
                                    (error_locations[2]>=0) ? coeffs[error_locations[2]] : -1,
                                    (error_locations[3]>=0) ? coeffs[error_locations[3]] : -1,
                                    (error_locations[4]>=0) ? coeffs[error_locations[4]] : -1);
                    printf("Agg0:VRA %d\n", a0_VRA);
                    print_RAs("Agg0:PRA", a0_PRAs);

                    printf("Agg1:VRA %d\n", a1_VRA);
                    print_RAs("Agg1:PRA", a1_PRAs);
                }
                */
                }
            }
            //printf("%d %d %d\n", a0_VRA, a1_VRA, a2_VRA);
        }
        printf("%d %d %d\n", a0_VRA, a1_VRA, a2_VRA);
        for (int i=0; i<16; i++) {
            printf("Conflict count: %d: %llu\n", i, conflict_cnt[i]);
        }
    }
}

/*
// aggressor0: VRA=0, PRA=0
ROW_ADDR_t a0_VRA = 0;
ROW_ADDR_t a0_PRA[OCT_CNT] = 0;

ROW_ADDR_t v0_0_PRA = SCRAMBLE(ROW_CNT-1, 1);
ROW_ADDR_t v0_1_PRA = SCRAMBLE(1, 1);

// auto-generated by calc_victim_PRAs()
ROW_ADDR_t v0_0_VRAs[OCT_CNT] = {
4095, 1365,  819,  273,  585,  195, 1117, 3103,  315,  105,  273,   91, 3855, 1285, 1509,  503, 2137, 3443,  983, 1693, 1517, 1871, 3531, 1177, 1057, 3083,  117,   39, 1107,  369,  999,  333,  381,  127, 2353, 3515, 1839,  613, 3555, 1185, 2681, 2259, 1805, 1967, 2283,  761,   65, 1387,   63,   21,  917, 1671, 1673, 1923, 3591, 1197, 1915, 3369, 2385,  795, 3109, 3767,  771,  257, 2071, 3421,   45,   15, 1121, 1739, 3167, 2421, 3731, 2609, 1193, 1763,  957,  319, 1691, 1929};
ROW_ADDR_t v0_1_VRAs[OCT_CNT] = {
   1, 2731, 3277, 3823, 3511, 3901, 2979,  993, 3781, 3991, 3823, 4005,  241, 2811, 2587, 3593, 1959,  653, 3113, 2403, 2579, 2225,  565, 2919, 3039, 1013, 3979, 4057, 2989, 3727, 3097, 3763, 3715, 3969, 1743,  581, 2257, 3483,  541, 2911, 1415, 1837, 2291, 2129, 1813, 3335, 4031, 2709, 4033, 4075, 3179, 2425, 2423, 2173,  505, 2899, 2181,  727, 1711, 3301,  987,  329, 3325, 3839, 2025,  675, 4051, 4081, 2975, 2357,  929, 1675,  365, 1487, 2903, 2333, 3139, 3777, 2405, 2167};

void calc_victim_PRAs()
{
    printf("V0_0 PRA: %d\n", v0_0_PRA);
    printf("V0_1 PRA: %d\n", v0_1_PRA);

    for (int i=0; i<OCT_CNT; i++) {
        for (int j=0; j<ROW_CNT; j++) {
            if (SCRAMBLE(j, coeffs[i])==v0_0_PRA) {
                v0_0_VRAs[i] = j;
            }
            if (SCRAMBLE(j, coeffs[i])==v0_1_PRA) {
                v0_1_VRAs[i] = j;
            }
        }
    }

    printf("COEFF\n");
    for (int i=0; i<OCT_CNT; i++) {
        printf("%4d, ", coeffs[i]);
    }
    printf("n\n");

    printf("V0_0 VRAs\n");
    for (int i=0; i<OCT_CNT; i++) {
        printf("%4d, ", v0_0_VRAs[i]);
    }
    printf("n\n");

    printf("V0_1 VRAs\n");
    for (int i=0; i<OCT_CNT; i++) {
        printf("%4d, ", v0_1_VRAs[i]);
    }
    printf("\n");
}

*/
