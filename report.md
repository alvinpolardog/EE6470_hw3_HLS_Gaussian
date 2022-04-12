# EE6470 HW3 Report
吳哲廷 學號:110061590

Link to [Github Repo](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian)
##

## High level synthesis of Gaussian Blur

In HW3, we are tasked with designing a synthesizable version of the Gaussian blue module created in the previous homeworks.
In my implementation, the Gaussian blur module receives one row of data at a time from the testbench, and store at most three row of data at any time. This implementation was directly carried from the previous homeworks, and so runs mostly in the same fashion.

For the memory arrays, since array size is somewhat large, and the indices use are constantly incrementing, I have chosen to not flatten the array. Instead the register banks were used, allowing for multiple acceses to be combined into single operations.

##  
## 

Table Of Content
-----
1. [Comparing Different Designs](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian/edit/main/report.md#comparing-different-designs)
    1. [No Optimization](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian/edit/main/report.md#almost-no-optimization)
    2. [Loop Unrolling I](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian/edit/main/report.md#loop-unrolling-i)
    3. [Loop Unrolling II](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian/edit/main/report.md#loop-unrolling-ii)
    4. [Loop Pipelining I](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian/edit/main/report.md#pipelining-i)
    5. [Loop Pipelining II](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian/edit/main/report.md#pipelining-ii)
2. [Overall Comparisons](https://github.com/alvinpolardog/EE6470_hw3_HLS_Gaussian/edit/main/report.md#overall-comparsion)

## Comparing Different Designs

### Almost No Optimization
In this version, only basic latency constraints were applied. Stratus directive for loop unrolling or pipelining were not used.

#### HLS with BASIC configuration:
```
Total run time = 26234950 ns
```

               +------------------------------------------------------------------------------------+
               |                                                                                    |
        00803: | Allocation Report for all threads:                                                 |
        00805: |                                                    Area/Instance                   |
        00805: |                                           ------------------------------     Total |
        00805: |                          Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ---------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |          SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |         SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |           SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |       SobelFilter_Mod_64Ux2U_2U_4      2     263.3(35)       987.4          2501.4 |
        00807: |      SobelFilter_Mul_12Sx8U_12S_1      1                     590.4           590.4 |
        00807: |      SobelFilter_Mul_12Sx8U_12S_4      1                     367.6           367.6 |
        00807: |      SobelFilter_Sub_9Ux32U_33S_1      1                     323.0           323.0 |
        00807: |                      mux_33bx2i0c      2                     102.4           204.9 |
        00807: |       SobelFilter_Mul_9Ux2U_10U_1      1                     166.3           166.3 |
        00807: |     SobelFilter_Add_12Ux12U_12U_1      1                     154.0           154.0 |
        00807: |                      mux_12bx2i1c      4                      32.6           130.4 |
        00807: |     SobelFilter_Add_10Ux10U_10U_1      1                     124.6           124.6 |
        00807: | SobelFilter_LessThan_11Sx10S_1U_4      2                      49.6            99.2 |
        00807: |                      mux_24bx3i0c      1                      76.8            76.8 |
        00807: |     SobelFilter_Add_12Ux12U_12U_4      1                      76.3            76.3 |
        00807: |                      mux_12bx2i0c      2                      37.3            74.5 |
        00807: |        SobelFilter_Add_9Ux1U_9U_1      1                      61.5            61.5 |
        00807: |                      mux_10bx5i1c      1                      53.2            53.2 |
        00807: |                       mux_8bx2i0c      2                      24.8            49.7 |
        00807: |                      mux_12bx3i0c      1                      39.4            39.4 |
        00807: |                      mux_12bx3i1c      1                      36.1            36.1 |
        00807: |       SobelFilter_Sub_9Ux2U_10S_4      1                      31.5            31.5 |
        00807: |                      mux_10bx2i0c      1                      31.0            31.0 |
        00807: |                       mux_9bx2i0c      1                      27.9            27.9 |
        00807: |                       mux_2bx2i1c      5                       5.4            27.2 |
        00807: |                       mux_9bx3i2c      1                      25.1            25.1 |
        00807: |                       mux_9bx2i1c      1                      24.4            24.4 |
        00807: |                       mux_1bx2i2c     10                       2.3            23.3 |
        00807: |                       mux_2bx3i3c      4                       5.4            21.8 |
        00807: |        SobelFilter_Sub_2Ux2U_3S_4      2                      10.3            20.5 |
        00807: |        SobelFilter_Add_4Ux2U_4U_4      1                      15.0            15.0 |
        00807: |                       mux_3bx5i5c      1                      13.8            13.8 |
        00807: |                       mux_2bx3i1c      2                       6.7            13.3 |
        00807: |        SobelFilter_Add_2Ux1U_2U_4      2                       6.2            12.3 |
        00807: |                       mux_4bx3i2c      1                      12.1            12.1 |
        00807: |        SobelFilter_Mul_2Ux2U_4U_4      1                      11.3            11.3 |
        00807: |   SobelFilter_LessThan_2Ux2U_1U_4      2                       5.1            10.3 |
        00807: |                       mux_3bx2i0c      1                       9.3             9.3 |
        00807: |   SobelFilter_LessThan_9Ux2U_1U_4      1                       9.2             9.2 |
        00807: |                       mux_2bx4i4c      1                       7.3             7.3 |
        00807: |        SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |           SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |          SobelFilter_gen_busy_r_4      1                       4.1             4.1 |
        00807: |                       mux_1bx3i1c      1                       3.8             3.8 |
        00807: |                       mux_1bx2i1c      1                       2.7             2.7 |
        00807: |        SobelFilter_N_Muxb_1_2_4_4      1                       2.4             2.4 |
        00807: |        SobelFilter_And_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |         SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |         SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                         registers     34                                           |
        01442: |                 Reg bits by type:                                                  |
        01442. |                    EN SS SC AS AC                                                  |
        00809: |                     0  0  1  0  0      2       5.5(1)          1.4                 |
        00809: |                     0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                     1  0  0  0  0    136       7.5(1)          0.0                 |
        00809: |                     1  0  1  0  0     25       7.5(1)          1.4                 |
        00809: |                     1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                 all register bits    165       7.5(1)          0.2          1275.0 |
        02604: |                   estimated cntrl      1                     142.1           142.1 |
        00811: | ---------------------------------------------------------------------------------- |
        00812: |                        Total Area         141527.8(18811)  61107.3   0.0  202635.1 |
               |                                                                                    |
               +------------------------------------------------------------------------------------+
               
               

#### HLS with DPA configuration (Datapath Optimization):
 ```
 Total run time = 26900590 ns
 ```
                +---------------------------------------------------------------------------------+
               |                                                                                 |
        00803: | Allocation Report for all threads:                                              |
        00805: |                                                 Area/Instance                   |
        00805: |                                        ------------------------------     Total |
        00805: |                       Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |       SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |      SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |        SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |    SobelFilter_Mod_64Ux2U_2U_4      2     263.3(35)       987.4          2501.4 |
        00807: | SobelFilter_Add2Mul2s12u8u12_4      2                     420.0           840.0 |
        00807: |  SobelFilter_Add_10Ux10U_10U_4      2                      66.0           132.0 |
        00807: |                   mux_33bx2i0c      1                     102.4           102.4 |
        00807: |                   mux_12bx2i1c      3                      32.6            97.8 |
        00807: |                   mux_24bx3i0c      1                      76.8            76.8 |
        00807: |                   mux_12bx2i0c      1                      37.3            37.3 |
        00807: | SobelFilter_Add2u9Mul2i258u2_4      1                      35.6            35.6 |
        00807: |                   mux_11bx2i0c      1                      34.1            34.1 |
        00807: |     SobelFilter_SubSubu2i3u9_4      1                      33.5            33.5 |
        00807: |       SobelFilter_Add_11S_15_4      1                      31.5            31.5 |
        00807: |         SobelFilter_Add2i1u9_4      1                      29.8            29.8 |
        00807: |          SobelFilter_Subi1u9_4      1                      29.1            29.1 |
        00807: |                    mux_9bx2i0c      1                      27.9            27.9 |
        00807: |                    mux_9bx3i1c      1                      27.6            27.6 |
        00807: |                    mux_9bx3i2c      1                      25.1            25.1 |
        00807: |                    mux_8bx2i0c      1                      24.8            24.8 |
        00807: |                    mux_9bx2i1c      1                      24.4            24.4 |
        00807: |                    mux_2bx3i3c      4                       5.4            21.8 |
        00807: |                    mux_2bx2i1c      4                       5.4            21.7 |
        00807: |                    mux_1bx2i2c      8                       2.3            18.6 |
        00807: |   SobelFilter_Add2u2Mul2i3u2_4      1                      17.8            17.8 |
        00807: |                    mux_2bx3i1c      2                       6.7            13.3 |
        00807: |                    mux_2bx2i0c      2                       6.2            12.4 |
        00807: |                    mux_4bx3i2c      1                      12.1            12.1 |
        00807: |        SobelFilter_gen000001_4      1                       8.2             8.2 |
        00807: |                    mux_2bx4i4c      1                       7.3             7.3 |
        00807: |         SobelFilter_LtiLLs11_4      1                       7.2             7.2 |
        00807: |         SobelFilter_Add2i1u2_4      2                       3.4             6.8 |
        00807: |           SobelFilter_Lti3u9_4      1                       6.5             6.5 |
        00807: |     SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |        SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |       SobelFilter_gen_busy_r_4      1                       4.1             4.1 |
        00807: |          SobelFilter_Subi1u2_4      1                       4.1             4.1 |
        00807: |                    mux_1bx3i1c      1                       3.8             3.8 |
        00807: |    SobelFilter_N_Muxb_1_2_20_4      1                       2.4             2.4 |
        00807: |           SobelFilter_Lti3u2_4      2                       1.0             2.1 |
        00807: |     SobelFilter_And_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |      SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |       SobelFilter_Mul2i258u2_4      1                       0.0             0.0 |
        00807: |      SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                      registers     28                                           |
        01442: |              Reg bits by type:                                                  |
        01442. |                 EN SS SC AS AC                                                  |
        00809: |                  0  0  1  0  0      2       5.5(1)          1.4                 |
        00809: |                  0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                  1  0  0  0  0    115       7.5(1)          0.0                 |
        00809: |                  1  0  1  0  0     19       7.5(1)          1.4                 |
        00809: |                  1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |              all register bits    138       7.5(1)          0.2          1063.6 |
        02604: |                estimated cntrl      1                     136.2           136.2 |
        00811: | ------------------------------------------------------------------------------- |
        00812: |                     Total Area         141324.7(18784)  59885.5   0.0  201210.1 |
               |                                                                                 |
               +---------------------------------------------------------------------------------+

#### Improvements:
The datapath optimization simulation time actually cause took '26900590/26234950' or '1.0253' time longer, that is, the optimization resulted in a 2% slowdown.
The estimated area however is '201210.1/ 202635.1' or 0.99296765466 times smaller, that is, around a 1% area reduction.
This is not a very significant tradeoff. The reason for such minute improvement, especially for the estimated area, may be that the most of the area are taken up by the memory arrays, and thus cannot be shrunken down even more through optimization.


### Loop Unrolling (I)
The read loop of the Gaussian noise module is unrolled with an unroll value of 6 and the CONSERVATIVE parameter.
#### HLS with BASIC configuration:
```
Total run time = 14882230 ns
```
               +------------------------------------------------------------------------------------+
               |                                                                                    |
        00803: | Allocation Report for all threads:                                                 |
        00805: |                                                    Area/Instance                   |
        00805: |                                           ------------------------------     Total |
        00805: |                          Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ---------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |          SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |         SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |           SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |       SobelFilter_Mod_64Ux2U_2U_4      2     263.3(35)       987.4          2501.4 |
        00807: |      SobelFilter_Mul_12Sx8U_12S_4      3                     367.6          1102.9 |
        00807: |      SobelFilter_Sub_9Ux32U_33S_1      2                     323.0           646.0 |
        00807: |     SobelFilter_Add_10Ux10U_10U_1      5                     124.6           623.0 |
        00807: |     SobelFilter_Add_33Sx10S_33S_4      2                     296.9           593.7 |
        00807: |       SobelFilter_Mul_9Ux2U_10U_1      2                     166.3           332.6 |
        00807: |     SobelFilter_Add_12Ux12U_12U_4      4                      76.3           305.1 |
        00807: | SobelFilter_LessThan_33Sx10S_1U_4      2                     125.9           251.7 |
        00807: |                      mux_10bx2i0c      8                      31.0           248.4 |
        00807: |                      mux_33bx7i1c      1                     239.8           239.8 |
        00807: |     SobelFilter_Add_10Ux10U_10U_4      3                      66.0           198.0 |
        00807: |                      mux_33bx4i0c      1                     140.8           140.8 |
        00807: |                      mux_10bx6i0c      2                      67.4           134.8 |
        00807: |                      mux_33bx4i1c      1                     132.0           132.0 |
        00807: |                      mux_24bx5i0c      1                     129.5           129.5 |
        00807: |                      mux_33bx2i0c      1                     102.4           102.4 |
        00807: |                      mux_32bx3i0c      1                     101.7           101.7 |
        00807: |                      mux_10bx3i0c      3                      33.2            99.6 |
        00807: |                      mux_32bx2i0c      1                      99.3            99.3 |
        00807: |                      mux_32bx3i1c      1                      93.2            93.2 |
        00807: |                      mux_32bx2i1c      1                      86.9            86.9 |
        00807: |                      mux_12bx2i0c      2                      37.3            74.5 |
        00807: |      SobelFilter_Sub_10Ux2U_10S_4      2                      34.2            68.4 |
        00807: |  SobelFilter_LessThan_32Ux2U_1U_4      3                      22.2            66.7 |
        00807: |                       mux_4bx9i9c      2                      33.3            66.7 |
        00807: |       SobelFilter_Add_9Ux3S_11S_4      1                      65.3            65.3 |
        00807: |                      mux_12bx2i1c      2                      32.6            65.2 |
        00807: |        SobelFilter_Add_9Ux1U_9U_1      1                      61.5            61.5 |
        00807: |                      mux_10bx3i1c      2                      30.4            60.9 |
        00807: |                      mux_12bx4i0c      1                      53.0            53.0 |
        00807: | SobelFilter_LessThan_11Sx10S_1U_4      1                      49.6            49.6 |
        00807: |        SobelFilter_Add_4Ux2U_4U_4      3                      15.0            45.1 |
        00807: |                      mux_10bx4i0c      1                      44.6            44.6 |
        00807: |                     mux_4bx11i11c      1                      40.8            40.8 |
        00807: |                       mux_3bx7i7c      2                      19.4            38.8 |
        00807: |                      mux_11bx3i0c      1                      36.3            36.3 |
        00807: |                      mux_12bx3i1c      1                      36.1            36.1 |
        00807: |        SobelFilter_Mul_2Ux2U_4U_4      3                      11.3            33.9 |
        00807: |                       mux_3bx6i6c      2                      16.6            33.2 |
        00807: |                       mux_9bx2i0c      1                      27.9            27.9 |
        00807: |        SobelFilter_Add_2Ux2U_2U_4      3                       8.6            25.7 |
        00807: |                       mux_8bx2i0c      1                      24.8            24.8 |
        00807: |                       mux_9bx2i1c      1                      24.4            24.4 |
        00807: |                       mux_1bx2i2c     10                       2.3            23.3 |
        00807: |                       mux_2bx3i3c      4                       5.4            21.8 |
        00807: |                       mux_4bx4i0c      1                      19.5            19.5 |
        00807: |                       mux_5bx4i3c      1                      19.2            19.2 |
        00807: |                       mux_2bx3i0c      2                       7.3            14.5 |
        00807: |                       mux_3bx5i5c      1                      13.8            13.8 |
        00807: |                       mux_2bx3i1c      2                       6.7            13.3 |
        00807: |                       mux_4bx2i0c      1                      12.4            12.4 |
        00807: |        SobelFilter_Sub_2Ux2U_3S_4      1                      10.3            10.3 |
        00807: |                       mux_3bx3i1c      1                      10.0            10.0 |
        00807: |   SobelFilter_LessThan_9Ux2U_1U_4      1                       9.2             9.2 |
        00807: |                       mux_2bx4i1c      1                       9.1             9.1 |
        00807: |                       mux_2bx4i4c      1                       7.3             7.3 |
        00807: |        SobelFilter_Add_2Ux1U_2U_4      1                       6.2             6.2 |
        00807: |                       mux_2bx2i1c      1                       5.4             5.4 |
        00807: |   SobelFilter_LessThan_2Ux2U_1U_4      1                       5.1             5.1 |
        00807: |        SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |           SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |          SobelFilter_gen_busy_r_4      1                       4.1             4.1 |
        00807: |                       mux_1bx3i1c      1                       3.8             3.8 |
        00807: |                       mux_1bx2i0c      1                       3.1             3.1 |
        00807: |        SobelFilter_N_Muxb_1_2_4_4      1                       2.4             2.4 |
        00807: |        SobelFilter_And_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |         SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |         SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                         registers     51                                           |
        01442: |                 Reg bits by type:                                                  |
        01442. |                    EN SS SC AS AC                                                  |
        00809: |                     0  0  1  0  0      2       5.5(1)          1.4                 |
        00809: |                     0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                     1  0  0  0  0    328       7.5(1)          0.0                 |
        00809: |                     1  0  1  0  0     50       7.5(1)          1.4                 |
        00809: |                     1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                 all register bits    382       7.5(1)          0.2          2941.9 |
        02604: |                   estimated cntrl      1                     533.4           533.4 |
        00811: | ---------------------------------------------------------------------------------- |
        00812: |                        Total Area         143160.5(19028)  65463.9   0.0  208624.4 |
               |                                                                                    |
               +------------------------------------------------------------------------------------+
#### HLS with DPA configuration
```
Total run time = 21335170 ns
```
               +-------------------------------------------------------------------------------------+
               |                                                                                     |
        00803: | Allocation Report for all threads:                                                  |
        00805: |                                                     Area/Instance                   |
        00805: |                                            ------------------------------     Total |
        00805: |                           Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ----------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |          SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |           SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |            SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |        SobelFilter_Mod_64Ux2U_2U_4      2     263.3(35)       987.4          2501.4 |
        00807: |     SobelFilter_Add2Mul2s12u8u12_4      2                     420.0           840.0 |
        00807: |                       mux_33bx9i0c      1                     320.6           320.6 |
        00807: |       SobelFilter_Add_33Sx2S_33S_4      1                     296.2           296.2 |
        00807: |                       mux_12bx2i0c      4                      37.3           149.0 |
        00807: |                       mux_32bx4i1c      1                     128.0           128.0 |
        00807: |             SobelFilter_LtiLLs32_4      6                      20.5           123.1 |
        00807: |                       mux_33bx3i0c      1                     104.8           104.8 |
        00807: |                       mux_33bx2i0c      1                     102.4           102.4 |
        00807: |                       mux_32bx2i1c      1                      86.9            86.9 |
        00807: |                       mux_10bx7i0c      1                      78.8            78.8 |
        00807: |                       mux_24bx3i0c      1                      76.8            76.8 |
        00807: |       SobelFilter_Add2Subi1u10u9_4      1                      71.5            71.5 |
        00807: |                       mux_12bx2i1c      2                      32.6            65.2 |
        00807: |                       mux_10bx2i0c      2                      31.0            62.1 |
        00807: |              SobelFilter_Lti3u32_4      3                      19.2            57.5 |
        00807: |                        mux_8bx2i0c      2                      24.8            49.7 |
        00807: |                      mux_4bx12i12c      1                      44.5            44.5 |
        00807: |    SobelFilter_Add2s10Mul2i258u2_4      1                      37.6            37.6 |
        00807: |         SobelFilter_SubSubu2i3u9_4      1                      33.5            33.5 |
        00807: |                        mux_4bx9i9c      1                      33.3            33.3 |
        00807: |                       mux_10bx3i0c      1                      33.2            33.2 |
        00807: |           SobelFilter_Add_11S_15_4      1                      31.5            31.5 |
        00807: |                       mux_11bx2i1c      1                      29.9            29.9 |
        00807: |             SobelFilter_Add2i1u9_4      1                      29.8            29.8 |
        00807: |              SobelFilter_Subi1u9_4      1                      29.1            29.1 |
        00807: |                        mux_9bx2i0c      1                      27.9            27.9 |
        00807: |                        mux_9bx2i1c      1                      24.4            24.4 |
        00807: |                        mux_6bx4i3c      1                      22.6            22.6 |
        00807: |                        mux_3bx8i8c      1                      22.2            22.2 |
        00807: |                        mux_1bx2i2c      9                       2.3            21.0 |
        00807: | SobelFilter_Add2u2Mul2i3Add2i3u2_4      1                      20.9            20.9 |
        00807: |                        mux_2bx3i1c      3                       6.7            20.0 |
        00807: |                        mux_3bx7i7c      1                      19.4            19.4 |
        00807: |                        mux_3bx5i5c      1                      13.8            13.8 |
        00807: |                        mux_2bx2i0c      2                       6.2            12.4 |
        00807: |                        mux_2bx3i3c      2                       5.4            10.9 |
        00807: |             SobelFilter_LtiLLs11_4      1                       8.2             8.2 |
        00807: |                        mux_2bx4i4c      1                       7.3             7.3 |
        00807: |               SobelFilter_Lti3u9_4      1                       6.5             6.5 |
        00807: |                        mux_2bx2i1c      1                       5.4             5.4 |
        00807: |         SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |            SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |           SobelFilter_gen_busy_r_4      1                       4.1             4.1 |
        00807: |                        mux_1bx3i1c      1                       3.8             3.8 |
        00807: |             SobelFilter_Add2i1u2_4      1                       3.4             3.4 |
        00807: |        SobelFilter_N_Muxb_1_2_19_4      1                       2.4             2.4 |
        00807: |         SobelFilter_And_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |          SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |               SobelFilter_Lti3u2_4      1                       1.0             1.0 |
        00807: |          SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                          registers     34                                           |
        01442: |                  Reg bits by type:                                                  |
        01442. |                     EN SS SC AS AC                                                  |
        00809: |                      0  0  1  0  0      2       5.5(1)          1.4                 |
        00809: |                      0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                      1  0  0  0  0    279       7.5(1)          0.0                 |
        00809: |                      1  0  1  0  0     35       7.5(1)          1.4                 |
        00809: |                      1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                  all register bits    318       7.5(1)          0.2          2439.8 |
        02604: |                    estimated cntrl      1                     469.1           469.1 |
        00811: | ----------------------------------------------------------------------------------- |
        00812: |                         Total Area         142679.0(18964)  61633.0   0.0  204312.0 |
               |                                                                                     |
               +-------------------------------------------------------------------------------------+
               
### Loop Unrolling (II)
The read loop of the Gaussian noise module is unrolled with an unroll value of 12 and the CONSERVATIVE parameter.
#### HLS with BASIC configuration:
```
Total run time = 15119590 ns
```
               +------------------------------------------------------------------------------------+
               |                                                                                    |
        00803: | Allocation Report for all threads:                                                 |
        00805: |                                                    Area/Instance                   |
        00805: |                                           ------------------------------     Total |
        00805: |                          Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ---------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |          SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |         SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |           SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |       SobelFilter_Mod_64Ux2U_2U_4      2     263.3(35)       987.4          2501.4 |
        00807: |      SobelFilter_Mul_12Sx8U_12S_4      3                     367.6          1102.9 |
        00807: |      SobelFilter_Sub_9Ux32U_33S_1      2                     323.0           646.0 |
        00807: |     SobelFilter_Add_10Ux10U_10U_1      5                     124.6           623.0 |
        00807: |                     mux_33bx16i1c      1                     563.4           563.4 |
        00807: |                     mux_32bx12i0c      1                     415.8           415.8 |
        00807: |       SobelFilter_Mul_9Ux2U_10U_1      2                     166.3           332.6 |
        00807: |     SobelFilter_Add_12Ux12U_12U_4      4                      76.3           305.1 |
        00807: |     SobelFilter_Add_33Sx10S_33S_4      1                     296.9           296.9 |
        00807: |     SobelFilter_Add_10Ux10U_10U_4      4                      66.0           264.0 |
        00807: |                      mux_10bx2i0c      8                      31.0           248.4 |
        00807: |                      mux_33bx5i0c      1                     176.7           176.7 |
        00807: |                     mux_10bx12i0c      1                     135.8           135.8 |
        00807: |                      mux_10bx3i0c      4                      33.2           132.8 |
        00807: | SobelFilter_LessThan_33Sx10S_1U_4      1                     125.9           125.9 |
        00807: |                     mux_10bx11i0c      1                     124.4           124.4 |
        00807: |                      mux_12bx2i0c      3                      37.3           111.8 |
        00807: |                      mux_33bx3i0c      1                     104.8           104.8 |
        00807: |                      mux_24bx4i0c      1                     103.1           103.1 |
        00807: |                      mux_32bx3i1c      1                      93.2            93.2 |
        00807: |                      mux_10bx4i0c      2                      44.6            89.2 |
        00807: |                     mux_4bx12i12c      2                      44.5            89.1 |
        00807: |                      mux_32bx2i1c      1                      86.9            86.9 |
        00807: |                      mux_12bx3i1c      2                      36.1            72.3 |
        00807: |      SobelFilter_Sub_10Ux2U_10S_4      2                      34.2            68.4 |
        00807: |  SobelFilter_LessThan_32Ux2U_1U_4      3                      22.2            66.7 |
        00807: |                       mux_4bx9i9c      2                      33.3            66.7 |
        00807: |       SobelFilter_Add_9Ux3S_11S_4      1                      65.3            65.3 |
        00807: |        SobelFilter_Add_9Ux1U_9U_1      1                      61.5            61.5 |
        00807: |                     mux_4bx16i16c      1                      59.5            59.5 |
        00807: |                      mux_10bx5i0c      1                      56.0            56.0 |
        00807: |                      mux_12bx4i1c      1                      49.6            49.6 |
        00807: | SobelFilter_LessThan_11Sx10S_1U_4      1                      49.6            49.6 |
        00807: |                     mux_4bx13i13c      1                      48.3            48.3 |
        00807: |                     mux_4bx11i11c      1                      40.8            40.8 |
        00807: |                      mux_12bx3i0c      1                      39.4            39.4 |
        00807: |                      mux_11bx2i0c      1                      34.1            34.1 |
        00807: |                      mux_10bx3i1c      1                      30.4            30.4 |
        00807: |        SobelFilter_Add_4Ux2U_4U_4      2                      15.0            30.1 |
        00807: |                       mux_9bx2i0c      1                      27.9            27.9 |
        00807: |                      mux_10bx2i1c      1                      27.2            27.2 |
        00807: |                       mux_2bx3i1c      4                       6.7            26.6 |
        00807: |                       mux_8bx2i0c      1                      24.8            24.8 |
        00807: |                       mux_9bx2i1c      1                      24.4            24.4 |
        00807: |                       mux_1bx2i2c     10                       2.3            23.3 |
        00807: |                       mux_6bx4i3c      1                      22.6            22.6 |
        00807: |        SobelFilter_Mul_2Ux2U_4U_4      2                      11.3            22.6 |
        00807: |                       mux_2bx3i3c      4                       5.4            21.8 |
        00807: |                       mux_3bx7i7c      1                      19.4            19.4 |
        00807: |        SobelFilter_Add_2Ux2U_2U_4      2                       8.6            17.1 |
        00807: |                       mux_4bx3i0c      1                      14.5            14.5 |
        00807: |                       mux_3bx5i5c      1                      13.8            13.8 |
        00807: |                       mux_4bx2i0c      1                      12.4            12.4 |
        00807: |        SobelFilter_Sub_2Ux2U_3S_4      1                      10.3            10.3 |
        00807: |                       mux_3bx3i1c      1                      10.0            10.0 |
        00807: |   SobelFilter_LessThan_9Ux2U_1U_4      1                       9.2             9.2 |
        00807: |                       mux_2bx4i4c      1                       7.3             7.3 |
        00807: |                       mux_2bx3i0c      1                       7.3             7.3 |
        00807: |        SobelFilter_Add_2Ux1U_2U_4      1                       6.2             6.2 |
        00807: |                       mux_2bx2i1c      1                       5.4             5.4 |
        00807: |   SobelFilter_LessThan_2Ux2U_1U_4      1                       5.1             5.1 |
        00807: |        SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |           SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |          SobelFilter_gen_busy_r_4      1                       4.1             4.1 |
        00807: |                       mux_1bx3i1c      1                       3.8             3.8 |
        00807: |                       mux_1bx2i0c      1                       3.1             3.1 |
        00807: |        SobelFilter_N_Muxb_1_2_4_4      1                       2.4             2.4 |
        00807: |        SobelFilter_And_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |         SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |         SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                         registers     62                                           |
        01442: |                 Reg bits by type:                                                  |
        01442. |                    EN SS SC AS AC                                                  |
        00809: |                     0  0  1  0  0      2       5.5(1)          1.4                 |
        00809: |                     0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                     1  0  0  0  0    586       7.5(1)          0.0                 |
        00809: |                     1  0  1  0  0     58       7.5(1)          1.4                 |
        00809: |                     1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                 all register bits    648       7.5(1)          0.1          4954.2 |
        02604: |                   estimated cntrl      1                     697.1           697.1 |
        00811: | ---------------------------------------------------------------------------------- |
        00812: |                        Total Area         145161.9(19294)  66102.9   0.0  211264.8 |
               |                                                                                    |
               +------------------------------------------------------------------------------------+


#### HLS with DPA configuration
```
Total run time = 21515770 ns
```
              +-------------------------------------------------------------------------------------+
               |                                                                                     |
        00803: | Allocation Report for all threads:                                                  |
        00805: |                                                     Area/Instance                   |
        00805: |                                            ------------------------------     Total |
        00805: |                           Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ----------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |          SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |           SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |            SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |        SobelFilter_Mod_64Ux2U_2U_4      2     263.3(35)       987.4          2501.4 |
        00807: |     SobelFilter_Add2Mul2s12u8u12_4      2                     420.0           840.0 |
        00807: |                      mux_33bx15i0c      1                     536.4           536.4 |
        00807: |       SobelFilter_Add_33Sx2S_33S_4      1                     296.2           296.2 |
        00807: |             SobelFilter_LtiLLs32_4     12                      20.5           246.2 |
        00807: |                       mux_12bx2i0c      4                      37.3           149.0 |
        00807: |                      mux_10bx13i0c      1                     147.2           147.2 |
        00807: |                       mux_33bx3i0c      1                     104.8           104.8 |
        00807: |                       mux_33bx2i0c      1                     102.4           102.4 |
        00807: |                       mux_12bx2i1c      3                      32.6            97.8 |
        00807: |                       mux_32bx2i1c      1                      86.9            86.9 |
        00807: |                      mux_5bx18i18c      1                      81.3            81.3 |
        00807: |                       mux_24bx3i0c      1                      76.8            76.8 |
        00807: |       SobelFilter_Add2Subi1u10u9_4      1                      71.5            71.5 |
        00807: |                       mux_10bx2i0c      2                      31.0            62.1 |
        00807: |              SobelFilter_Lti3u32_4      3                      19.2            57.5 |
        00807: |                      mux_4bx15i15c      1                      55.8            55.8 |
        00807: |                      mux_4bx14i14c      1                      52.0            52.0 |
        00807: |                        mux_8bx2i0c      2                      24.8            49.7 |
        00807: |                      mux_4bx13i13c      1                      48.3            48.3 |
        00807: |    SobelFilter_Add2s10Mul2i258u2_4      1                      37.6            37.6 |
        00807: |         SobelFilter_SubSubu2i3u9_4      1                      33.5            33.5 |
        00807: |                       mux_10bx3i0c      1                      33.2            33.2 |
        00807: |           SobelFilter_Add_11S_15_4      1                      31.5            31.5 |
        00807: |                       mux_11bx2i1c      1                      29.9            29.9 |
        00807: |             SobelFilter_Add2i1u9_4      1                      29.8            29.8 |
        00807: |              SobelFilter_Subi1u9_4      1                      29.1            29.1 |
        00807: |                        mux_9bx2i0c      1                      27.9            27.9 |
        00807: |                        mux_9bx2i1c      1                      24.4            24.4 |
        00807: |                        mux_6bx4i3c      1                      22.6            22.6 |
        00807: |                        mux_1bx2i2c      9                       2.3            21.0 |
        00807: | SobelFilter_Add2u2Mul2i3Add2i3u2_4      1                      20.9            20.9 |
        00807: |                        mux_2bx3i1c      3                       6.7            20.0 |
        00807: |                        mux_3bx5i5c      1                      13.8            13.8 |
        00807: |                        mux_2bx2i0c      2                       6.2            12.4 |
        00807: |                        mux_2bx3i3c      2                       5.4            10.9 |
        00807: |             SobelFilter_LtiLLs11_4      1                       8.2             8.2 |
        00807: |                        mux_2bx4i4c      1                       7.3             7.3 |
        00807: |               SobelFilter_Lti3u9_4      1                       6.5             6.5 |
        00807: |                        mux_2bx2i1c      1                       5.4             5.4 |
        00807: |         SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |            SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |           SobelFilter_gen_busy_r_4      1                       4.1             4.1 |
        00807: |                        mux_1bx3i1c      1                       3.8             3.8 |
        00807: |             SobelFilter_Add2i1u2_4      1                       3.4             3.4 |
        00807: |        SobelFilter_N_Muxb_1_2_19_4      1                       2.4             2.4 |
        00807: |         SobelFilter_And_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |          SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |               SobelFilter_Lti3u2_4      1                       1.0             1.0 |
        00807: |          SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                          registers     41                                           |
        01442: |                  Reg bits by type:                                                  |
        01442. |                     EN SS SC AS AC                                                  |
        00809: |                      0  0  1  0  0      2       5.5(1)          1.4                 |
        00809: |                      0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                      1  0  0  0  0    483       7.5(1)          0.0                 |
        00809: |                      1  0  1  0  0     38       7.5(1)          1.4                 |
        00809: |                      1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                  all register bits    525       7.5(1)          0.1          4001.4 |
        02604: |                    estimated cntrl      1                     738.6           738.6 |
        00811: | ----------------------------------------------------------------------------------- |
        00812: |                         Total Area         144236.4(19171)  62336.4   0.0  206572.8 |
               |                                                                                     |
               +-------------------------------------------------------------------------------------+

#### Improvements:
In both loop unrolling cases, the total area used was increased by 1~5% compared to the non-optimized version. However the runtime has a dramatic decrease, especially
in the case of the BASIC config. Since loop unrolling compromises between area and time by using more resources and parallelizing workload, it is apparent
that the large increase in area (above 3%) contributed greatly to the over 40% reduction in simulation runtime.

### Pipelining (I)
The read loop of the Gaussian noise module is pipelined with 1 iteration inbetween and the SOFT_STALL paramter

#### HLS with BASIC configuration
```
Total run time = 11811910 ns
```
               +-------------------------------------------------------------------------------------+
               |                                                                                     |
        00803: | Allocation Report for all threads:                                                  |
        00805: |                                                     Area/Instance                   |
        00805: |                                            ------------------------------     Total |
        00805: |                           Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ----------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |           SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |          SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |            SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |        SobelFilter_Mod_64Ux2U_2U_4      3     263.3(35)       987.4          3752.1 |
        00807: |       SobelFilter_Mul_12Sx8U_12S_4      3                     367.6          1102.9 |
        00807: |        SobelFilter_Mul_9Ux2U_10U_1      3                     166.3           498.9 |
        00807: |      SobelFilter_Add_10Ux10U_10U_1      3                     124.6           373.8 |
        00807: |       SobelFilter_Sub_9Ux32U_33S_1      1                     323.0           323.0 |
        00807: |      SobelFilter_Add_12Ux12U_12U_4      3                      76.3           228.8 |
        00807: |                       mux_33bx2i0c      1                     102.4           102.4 |
        00807: |  SobelFilter_LessThan_11Sx10S_1U_4      2                      49.6            99.2 |
        00807: |      SobelFilter_Add_11Sx10S_11S_4      1                      71.1            71.1 |
        00807: |          SobelFilter_N_Mux_2_2_6_1      3                      23.5            70.5 |
        00807: |                       mux_12bx2i1c      2                      32.6            65.2 |
        00807: |                       mux_10bx2i0c      2                      31.0            62.1 |
        00807: |         SobelFilter_N_Mux_24_2_0_4      1                      57.5            57.5 |
        00807: |                        mux_9bx2i1c      2                      24.4            48.9 |
        00807: |                       mux_12bx3i1c      1                      36.1            36.1 |
        00807: |         SobelFilter_Add_9Ux1U_9U_4      1                      32.8            32.8 |
        00807: |                       mux_11bx3i2c      1                      30.3            30.3 |
        00807: |                        mux_1bx2i1c     10                       2.7            27.2 |
        00807: | SobelFilter_gen_fifo_addr_1_alt0_4      3                       8.6            25.7 |
        00807: |         SobelFilter_Sub_2Ux2U_3S_4      2                      10.3            20.5 |
        00807: |                        mux_1bx2i2c      8                       2.3            18.6 |
        00807: |                        mux_2bx2i0c      3                       6.2            18.6 |
        00807: |                        mux_2bx2i1c      3                       5.4            16.3 |
        00807: |         SobelFilter_Add_4Ux2U_4U_4      1                      15.0            15.0 |
        00807: |          SobelFilter_N_Mux_2_2_6_4      3                       4.8            14.4 |
        00807: |         SobelFilter_Add_2Ux1U_2U_4      2                       6.2            12.3 |
        00807: |                        mux_3bx4i3c      1                      11.9            11.9 |
        00807: |         SobelFilter_Mul_2Ux2U_4U_4      1                      11.3            11.3 |
        00807: |    SobelFilter_LessThan_2Ux2U_1U_4      2                       5.1            10.3 |
        00807: |    SobelFilter_LessThan_9Ux2U_1U_4      1                       9.2             9.2 |
        00807: |       SobelFilter_Equal_1Ux1U_1U_1      2                       4.4             8.9 |
        00807: |         SobelFilter_Add_2Ux2U_2U_4      1                       8.6             8.6 |
        00807: |                        mux_3bx2i1c      1                       8.1             8.1 |
        00807: |                        mux_1bx3i1c      2                       3.8             7.6 |
        00807: |         SobelFilter_And_1Ux1U_1U_4      4                       1.4             5.5 |
        00807: |           SobelFilter_gen_busy_r_4      1                       5.5             5.5 |
        00807: |                        mux_2bx3i3c      1                       5.4             5.4 |
        00807: |         SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |            SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |                        mux_1bx3i2c      1                       3.5             3.5 |
        00807: |                        mux_1bx2i0c      1                       3.1             3.1 |
        00807: |         SobelFilter_N_Muxb_1_2_5_4      1                       2.4             2.4 |
        00807: |          SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |            SobelFilter_Not_1U_1U_4      1                       0.7             0.7 |
        00807: |          SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                          registers     42                                           |
        01442: |                  Reg bits by type:                                                  |
        01442. |                     EN SS SC AS AC                                                  |
        00809: |                      0  0  0  0  0      6       5.5(1)          0.0                 |
        00809: |                      0  0  1  0  0      7       5.5(1)          1.4                 |
        00809: |                      0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                      1  0  0  0  0    156       7.5(1)          0.0                 |
        00809: |                      1  0  1  0  0      9       7.5(1)          1.4                 |
        00809: |                      1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                  all register bits    180       7.4(1)          0.1          1350.2 |
        02604: |                    estimated cntrl      1                     255.7           255.7 |
        00811: | ----------------------------------------------------------------------------------- |
        00812: |                         Total Area         141881.4(18861)  62678.3   0.0  204559.8 |
               |                                                                                     |
               +-------------------------------------------------------------------------------------+

#### HLS with DPA configuration
```
Total run time = 11811910 ns
```
               +-------------------------------------------------------------------------------------+
               |                                                                                     |
        00803: | Allocation Report for all threads:                                                  |
        00805: |                                                     Area/Instance                   |
        00805: |                                            ------------------------------     Total |
        00805: |                           Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ----------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |           SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |          SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |            SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |        SobelFilter_Mod_64Ux2U_2U_4      3     263.3(35)       987.4          3752.1 |
        00807: |     SobelFilter_Add2Mul2s12u8u12_4      3                     420.0          1259.9 |
        00807: |      SobelFilter_Add_10Ux10U_10U_4      4                      66.0           264.0 |
        00807: |     SobelFilter_Add2u9Mul2i258u2_4      3                      35.6           106.7 |
        00807: |                       mux_33bx2i0c      1                     102.4           102.4 |
        00807: |                       mux_12bx2i1c      3                      32.6            97.8 |
        00807: |         SobelFilter_N_Mux_2_2_35_1      3                      23.5            70.5 |
        00807: |           SobelFilter_Add_11S_16_4      2                      31.5            62.9 |
        00807: |        SobelFilter_N_Mux_24_2_30_4      1                      57.5            57.5 |
        00807: |                        mux_9bx2i1c      2                      24.4            48.9 |
        00807: |                       mux_11bx4i2c      1                      42.7            42.7 |
        00807: |                       mux_11bx2i0c      1                      34.1            34.1 |
        00807: |         SobelFilter_SubSubu2i3u9_4      1                      33.5            33.5 |
        00807: |             SobelFilter_Add2i1u9_4      1                      29.8            29.8 |
        00807: |              SobelFilter_Subi1u9_4      1                      29.1            29.1 |
        00807: |                        mux_1bx2i1c     10                       2.7            27.2 |
        00807: | SobelFilter_gen_fifo_addr_1_alt0_4      3                       8.6            25.7 |
        00807: | SobelFilter_Add2u2Mul2i3Add2i3u2_4      1                      20.9            20.9 |
        00807: |                        mux_1bx2i2c      8                       2.3            18.6 |
        00807: |                        mux_2bx2i1c      3                       5.4            16.3 |
        00807: |         SobelFilter_N_Mux_2_2_35_4      3                       4.8            14.4 |
        00807: |                        mux_3bx4i3c      1                      11.9            11.9 |
        00807: |       SobelFilter_Equal_1Ux1U_1U_1      2                       4.4             8.9 |
        00807: |            SobelFilter_gen000001_4      1                       8.2             8.2 |
        00807: |                        mux_1bx3i1c      2                       3.8             7.6 |
        00807: |             SobelFilter_LtiLLs11_4      1                       7.2             7.2 |
        00807: |             SobelFilter_Add2i1u2_4      2                       3.4             6.8 |
        00807: |               SobelFilter_Lti3u9_4      1                       6.5             6.5 |
        00807: |         SobelFilter_And_1Ux1U_1U_4      4                       1.4             5.5 |
        00807: |           SobelFilter_gen_busy_r_4      1                       5.5             5.5 |
        00807: |         SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |            SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |              SobelFilter_Subi1u2_4      1                       4.1             4.1 |
        00807: |                        mux_1bx3i2c      1                       3.5             3.5 |
        00807: |                        mux_1bx2i0c      1                       3.1             3.1 |
        00807: |        SobelFilter_N_Muxb_1_2_21_4      1                       2.4             2.4 |
        00807: |               SobelFilter_Lti3u2_4      2                       1.0             2.1 |
        00807: |          SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |            SobelFilter_Not_1U_1U_4      1                       0.7             0.7 |
        00807: |           SobelFilter_Mul2i258u2_4      3                       0.0             0.0 |
        00807: |          SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                          registers     42                                           |
        01442: |                  Reg bits by type:                                                  |
        01442. |                     EN SS SC AS AC                                                  |
        00809: |                      0  0  0  0  0      6       5.5(1)          0.0                 |
        00809: |                      0  0  1  0  0      7       5.5(1)          1.4                 |
        00809: |                      0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                      1  0  0  0  0    167       7.5(1)          0.0                 |
        00809: |                      1  0  1  0  0      7       7.5(1)          1.4                 |
        00809: |                      1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                  all register bits    189       7.4(1)          0.1          1415.2 |
        02604: |                    estimated cntrl      1                     251.8           251.8 |
        00811: | ----------------------------------------------------------------------------------- |
        00812: |                         Total Area         141949.2(18870)  61644.3   0.0  203593.4 |
               |                                                                                     |
               +-------------------------------------------------------------------------------------+

### Pipelining (II)
The read loop of the Gaussian noise module is pipelined with 2 iteration inbetween and the SOFT_STALL paramter

#### HLS with BASIC configuration
```
Total run time = 12472390 ns
```
               +------------------------------------------------------------------------------------+
               |                                                                                    |
        00803: | Allocation Report for all threads:                                                 |
        00805: |                                                    Area/Instance                   |
        00805: |                                           ------------------------------     Total |
        00805: |                          Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ---------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |          SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |         SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |           SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |       SobelFilter_Mod_64Ux2U_2U_4      3     263.3(35)       987.4          3752.1 |
        00807: |      SobelFilter_Mul_12Sx8U_12S_4      3                     367.6          1102.9 |
        00807: |       SobelFilter_Mul_9Ux2U_10U_1      3                     166.3           498.9 |
        00807: |     SobelFilter_Add_10Ux10U_10U_1      3                     124.6           373.8 |
        00807: |      SobelFilter_Sub_9Ux32U_33S_1      1                     323.0           323.0 |
        00807: |     SobelFilter_Add_12Ux12U_12U_4      3                      76.3           228.8 |
        00807: |                      mux_33bx2i0c      1                     102.4           102.4 |
        00807: | SobelFilter_LessThan_11Sx10S_1U_4      2                      49.6            99.2 |
        00807: |                      mux_12bx2i1c      3                      32.6            97.8 |
        00807: |     SobelFilter_Add_11Sx10S_11S_4      1                      71.1            71.1 |
        00807: |                      mux_10bx2i0c      2                      31.0            62.1 |
        00807: |        SobelFilter_N_Mux_24_2_0_4      1                      57.5            57.5 |
        00807: |                       mux_9bx2i1c      2                      24.4            48.9 |
        00807: |        SobelFilter_Add_9Ux1U_9U_4      1                      32.8            32.8 |
        00807: |                      mux_11bx3i2c      1                      30.3            30.3 |
        00807: |                       mux_9bx2i0c      1                      27.9            27.9 |
        00807: |        SobelFilter_Sub_2Ux2U_3S_4      2                      10.3            20.5 |
        00807: |                       mux_2bx2i1c      3                       5.4            16.3 |
        00807: |        SobelFilter_Add_4Ux2U_4U_4      1                      15.0            15.0 |
        00807: |        SobelFilter_Add_2Ux1U_2U_4      2                       6.2            12.3 |
        00807: |                       mux_3bx4i3c      1                      11.9            11.9 |
        00807: |        SobelFilter_Mul_2Ux2U_4U_4      1                      11.3            11.3 |
        00807: |   SobelFilter_LessThan_2Ux2U_1U_4      2                       5.1            10.3 |
        00807: |                       mux_1bx2i2c      4                       2.3             9.3 |
        00807: |   SobelFilter_LessThan_9Ux2U_1U_4      1                       9.2             9.2 |
        00807: |        SobelFilter_Add_2Ux2U_2U_4      1                       8.6             8.6 |
        00807: |                       mux_3bx2i1c      1                       8.1             8.1 |
        00807: |                       mux_1bx3i1c      2                       3.8             7.6 |
        00807: |        SobelFilter_And_1Ux1U_1U_4      4                       1.4             5.5 |
        00807: |          SobelFilter_gen_busy_r_4      1                       5.5             5.5 |
        00807: |                       mux_2bx3i3c      1                       5.4             5.4 |
        00807: |                       mux_1bx2i1c      2                       2.7             5.4 |
        00807: |        SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |      SobelFilter_Equal_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |           SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |        SobelFilter_N_Muxb_1_2_5_4      1                       2.4             2.4 |
        00807: |         SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |           SobelFilter_Not_1U_1U_4      1                       0.7             0.7 |
        00807: |         SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                         registers     29                                           |
        01442: |                 Reg bits by type:                                                  |
        01442. |                    EN SS SC AS AC                                                  |
        00809: |                     0  0  1  0  0      3       5.5(1)          1.4                 |
        00809: |                     0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                     1  0  0  0  0    151       7.5(1)          0.0                 |
        00809: |                     1  0  1  0  0      8       7.5(1)          1.4                 |
        00809: |                     1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                 all register bits    164       7.5(1)          0.1          1243.5 |
        02604: |                   estimated cntrl      1                     100.8           100.8 |
        00811: | ---------------------------------------------------------------------------------- |
        00812: |                        Total Area         141781.6(18845)  62369.8   0.0  204151.4 |
               |                                                                                    |
               +------------------------------------------------------------------------------------+
               
#### HLS with DPA configuration
```
Total run time = 12472390 ns
```
               +-------------------------------------------------------------------------------------+
               |                                                                                     |
        00803: | Allocation Report for all threads:                                                  |
        00805: |                                                     Area/Instance                   |
        00805: |                                            ------------------------------     Total |
        00805: |                           Resource  Count       Seq(#FF)       Comb    BB      Area |
        00805: | ----------------------------------  -----  ---------------  -------  ----  -------- |
        00807: |           SobelFilter_blue_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |          SobelFilter_green_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |            SobelFilter_red_regbank      1   46588.6(6192)   18650.6         65239.3 |
        00807: |        SobelFilter_Mod_64Ux2U_2U_4      3     263.3(35)       987.4          3752.1 |
        00807: |     SobelFilter_Add2Mul2s12u8u12_4      3                     420.0          1259.9 |
        00807: |      SobelFilter_Add_10Ux10U_10U_4      3                      66.0           198.0 |
        00807: |                       mux_33bx2i0c      1                     102.4           102.4 |
        00807: |                       mux_12bx2i1c      3                      32.6            97.8 |
        00807: |                       mux_24bx2i0c      1                      74.5            74.5 |
        00807: |      SobelFilter_Add_11Sx10S_11S_4      1                      71.1            71.1 |
        00807: |     SobelFilter_Add2u9Mul2i258u2_4      2                      35.6            71.1 |
        00807: |                       mux_11bx3i1c      2                      33.3            66.6 |
        00807: |        SobelFilter_N_Mux_24_2_30_4      1                      57.5            57.5 |
        00807: |                        mux_9bx2i1c      2                      24.4            48.9 |
        00807: |         SobelFilter_SubSubu2i3u9_4      1                      33.5            33.5 |
        00807: |                       mux_10bx3i1c      1                      30.4            30.4 |
        00807: |             SobelFilter_Add2i1u9_4      1                      29.8            29.8 |
        00807: |              SobelFilter_Subi1u9_4      1                      29.1            29.1 |
        00807: |                        mux_9bx2i0c      1                      27.9            27.9 |
        00807: | SobelFilter_Add2u2Mul2i3Add2i3u2_4      1                      20.9            20.9 |
        00807: |                        mux_2bx2i1c      3                       5.4            16.3 |
        00807: |                        mux_3bx4i3c      1                      11.9            11.9 |
        00807: |                        mux_1bx2i2c      5                       2.3            11.6 |
        00807: |                        mux_2bx3i3c      2                       5.4            10.9 |
        00807: |            SobelFilter_gen000001_4      1                       8.2             8.2 |
        00807: |                        mux_1bx3i1c      2                       3.8             7.6 |
        00807: |             SobelFilter_LtiLLs11_4      1                       7.2             7.2 |
        00807: |             SobelFilter_Add2i1u2_4      2                       3.4             6.8 |
        00807: |               SobelFilter_Lti3u9_4      1                       6.5             6.5 |
        00807: |         SobelFilter_And_1Ux1U_1U_4      4                       1.4             5.5 |
        00807: |           SobelFilter_gen_busy_r_4      1                       5.5             5.5 |
        00807: |                        mux_1bx2i1c      2                       2.7             5.4 |
        00807: |         SobelFilter_Xor_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |       SobelFilter_Equal_1Ux1U_1U_1      1                       4.4             4.4 |
        00807: |            SobelFilter_Not_1U_1U_1      1                       4.1             4.1 |
        00807: |              SobelFilter_Subi1u2_4      1                       4.1             4.1 |
        00807: |        SobelFilter_N_Muxb_1_2_21_4      1                       2.4             2.4 |
        00807: |               SobelFilter_Lti3u2_4      2                       1.0             2.1 |
        00807: |          SobelFilter_Or_1Ux1U_1U_4      1                       1.4             1.4 |
        00807: |            SobelFilter_Not_1U_1U_4      1                       0.7             0.7 |
        00807: |           SobelFilter_Mul2i258u2_4      3                       0.0             0.0 |
        00807: |          SobelFilter_ROM_9X32_mask      1                               ?         ? |
        00808: |                          registers     31                                           |
        01442: |                  Reg bits by type:                                                  |
        01442. |                     EN SS SC AS AC                                                  |
        00809: |                      0  0  1  0  0      3       5.5(1)          1.4                 |
        00809: |                      0  1  0  0  0      1       5.5(1)          1.4                 |
        00809: |                      1  0  0  0  0    162       7.5(1)          0.0                 |
        00809: |                      1  0  1  0  0     10       7.5(1)          1.4                 |
        00809: |                      1  1  0  0  0      1       7.5(1)          1.4                 |
        00809: |                  all register bits    177       7.5(1)          0.1          1344.1 |
        02604: |                    estimated cntrl      1                     107.5           107.5 |
        00811: | ----------------------------------------------------------------------------------- |
        00812: |                         Total Area         141879.4(18858)  61388.5   0.0  203267.9 |
               |                                                                                     |
               +-------------------------------------------------------------------------------------+

## Overall Comparsion

Optimization | Runtime(ns) | Runtime Difference | Area | Area Difference
---|---|---|---|---
No Optimization | 26234950 | 0% | 202635 | 0%
No Optimization (DPA) | 26900590 | +2.5% | 201210 | -0.7%
Loop Unrolling I | 14882230 | -43.2% | 208624 | +2.9%
Loop Unrolling I (DPA) | 21335170 | -18.7% | 204312 | +0.8%
Loop Unrolling II | 15119590 | -42.4% | 211264 | +4.2%
Loop Unrolling II (DPA) | 21515770 | -18.0% | 206572 | +1.9%
Loop Pipelining I | 11811910 | -54.0% | 208624 | +1.0%
Loop Pipelining I (DPA) | 11811910 | -54.0% | 203593 | +0.5%
Loop Pipelining II | 12472390 | -52.4% | 204151 | +0.8%
Loop Pipelining II (DPA) | 12472390 | -52.4% | 206572 | +1.9%

In the above table, each of the optimizations have been organized and compared with the 1st synthesis with no optimization.

From the various experimentation, it is clear that loop optimization has a immense impact on simulation runtime. Since most of the estimated area is used
by the memory array, optimization does not create a great difference between the area used by each optimization. In this case, using loop pipelining may be
best choice.

It may be possible to create better runtime by coalescing loop, but in my experimentation, my current implementation keeps encountering bugs when using such method.


