//*****************************************************************************
//  Copyright (c) 2021 Glenfly Tech Co., Ltd..
//  All Rights Reserved.
//
//  This is UNPUBLISHED PROPRIETARY SOURCE CODE of Glenfly Tech Co., Ltd..;
//  the contents of this file may not be disclosed to third parties, copied or
//  duplicated in any form, in whole or in part, without the prior written
//  permission of Glenfly Tech Co., Ltd..
//
//  The copyright of the source code is protected by the copyright laws of the People's
//  Republic of China and the related laws promulgated by the People's Republic of China
//  and the international covenant(s) ratified by the People's Republic of China.
//*****************************************************************************


#include "CBiosChipShare.h"

CBIOS_S64 YCbCr601_fr_RGB[][3] = {  {269391,  528872, 102711},
                                   {-155485, -305252, 460738},
                                    {460738, -385810, -74927}};

CBIOS_S64 RGB_fr_YCbCr601[][3] = { {1220356,       0, 1672876} ,
                                   {1220356, -410625, -852112},
                                   {1220356, 2114363, 0} };

CBIOS_S64 YCbCr709_fr_RGB[][3] = {  {191547,  644378,  65050},
                                   {-105575, -355162, 460738},
                                    {460738, -418490, -42247}};

CBIOS_S64 RGB_fr_YCbCr709[][3] = { {1220356,      0 , 1879062},
                                   {1220356, -223516, -558569},
                                   {1220356, 2214115,     0} };

CBIOS_S64 YCbCr2020_fr_RGB[][3] = {{236686,  610861,  53428},
                                  {-128665, -332072, 460738},
                                   {460738, -423681, -37056} };// non constant luminance only

CBIOS_S64 RGB_fr_YCbCr2020[][3] = { {1220356, 0, 1759503},
                                    {1220356, -196345, -681742},
                                    {1220356, 2244899, 0} };

CBIOS_S64 LimitedRGB_fr_RGB[][3] = { {900976,      0, 0},
                                          {0, 900976, 0},
                                          {0,      0, 900976} };

CBIOS_S64 RGB_fr_LimitedRGB[][3] = { {1220356,       0, 0},
                                           {0, 1220356, 0},
                                           {0,       0, 1220356}};

CBIOS_S64 YCbCr709_fr_YCbCr601[][3] = {{1048576, -120831, -217087},
                                             {0, 1069055, 120831},
                                             {0,   77824, 1075200}};

CBIOS_S64 YCbCr601_fr_YCbCr709[][3] = {{1048576,  104447,  200703},
                                             {0, 1038335, -116735},
                                             {0,  -75776, 1030144} };

CBIOS_S64 Balance_Times_matrix[][3] = {{1048576, 0, 0},
                                             {0, 1048576, 0},
                                             {0, 0, 1048576}};

//map cosX' value  (X range from -180' to 180') to CSC_cos[0 ... 360]
CBIOS_S32  CSC_cos[]={ -1048576 ,-1048416 ,-1047937 ,-1047138 ,-1046021 ,-1044585 ,-1042831 ,-1040760 ,-1038371 ,-1035666 ,-1032645 ,-1029310 ,-1025662 ,-1021701 ,-1017428 ,-1012846 ,-1007955 ,-1002758 , -997255 , -991448 ,
                        -985339 , -978930 , -972222 , -965219 , -957921 , -950332 , -942453 , -934288 , -925837 , -917105 , -908093 , -898805 , -889242 , -879409 , -869308 , -858943 , -848315 , -837430 , -826289 , -814896 ,
                        -803255 , -791370 , -779243 , -766879 , -754282 , -741455 , -728402 , -715127 , -701634 , -687927 , -674011 , -659890 , -645567 , -631048 , -616337 , -601438 , -586356 , -571095 , -555660 , -540056 ,
                        -524288 , -508359 , -492276 , -476043 , -459665 , -443147 , -426494 , -409711 , -392803 , -375776 , -358634 , -341382 , -324027 , -306573 , -289026 , -271391 , -253673 , -235878 , -218011 , -200077 ,
                        -182083 , -164033 , -145933 , -127789 , -109606 ,  -91389 ,  -73144 ,  -54878 ,  -36594 ,  -18300 ,       0 ,   18300 ,   36594 ,   54878 ,   73144 ,   91389 ,  109606 ,  127789 ,  145933 ,  164033 ,
                         182083 ,  200077 ,  218011 ,  235878 ,  253673 ,  271391 ,  289026 ,  306573 ,  324027 ,  341382 ,  358634 ,  375776 ,  392803 ,  409711 ,  426494 ,  443147 ,  459665 ,  476043 ,  492276 ,  508359 ,
                         524287 ,  540056 ,  555660 ,  571095 ,  586356 ,  601438 ,  616337 ,  631048 ,  645567 ,  659890 ,  674011 ,  687927 ,  701634 ,  715127 ,  728402 ,  741455 ,  754282 ,  766879 ,  779243 ,  791370 ,
                         803255 ,  814896 ,  826289 ,  837430 ,  848315 ,  858943 ,  869308 ,  879409 ,  889242 ,  898805 ,  908093 ,  917105 ,  925837 ,  934288 ,  942453 ,  950332 ,  957921 ,  965219 ,  972222 ,  978930 ,
                         985339 ,  991448 ,  997255 , 1002758 , 1007955 , 1012846 , 1017428 , 1021701 , 1025662 , 1029310 , 1032645 , 1035666 , 1038371 , 1040760 , 1042831 , 1044585 , 1046021 , 1047138 , 1047937 , 1048416 ,
                        1048576 , 1048416 , 1047937 , 1047138 , 1046021 , 1044585 , 1042831 , 1040760 , 1038371 , 1035666 , 1032645 , 1029310 , 1025662 , 1021701 , 1017428 , 1012846 , 1007955 , 1002758 ,  997255 ,  991448 ,
                         985339 ,  978930 ,  972222 ,  965219 ,  957921 ,  950332 ,  942453 ,  934288 ,  925837 ,  917105 ,  908093 ,  898805 ,  889242 ,  879409 ,  869308 ,  858943 ,  848315 ,  837430 ,  826289 ,  814896 ,
                         803255 ,  791370 ,  779243 ,  766879 ,  754282 ,  741455 ,  728402 ,  715127 ,  701634 ,  687927 ,  674011 ,  659890 ,  645567 ,  631048 ,  616337 ,  601438 ,  586356 ,  571095 ,  555660 ,  540056 ,
                         524287 ,  508359 ,  492276 ,  476043 ,  459665 ,  443147 ,  426494 ,  409711 ,  392803 ,  375776 ,  358634 ,  341382 ,  324027 ,  306573 ,  289026 ,  271391 ,  253673 ,  235878 ,  218011 ,  200077 ,
                         182083 ,  164033 ,  145933 ,  127789 ,  109606 ,   91389 ,   73144 ,   54878 ,   36594 ,   18300 ,       0 ,  -18300 ,  -36594 ,  -54878 ,  -73144 ,  -91389 , -109606 , -127789 , -145933 , -164033 ,
                        -182083 , -200077 , -218011 , -235878 , -253673 , -271391 , -289026 , -306573 , -324027 , -341382 , -358634 , -375776 , -392803 , -409711 , -426494 , -443147 , -459665 , -476043 , -492276 , -508359 ,
                        -524288 , -540056 , -555660 , -571095 , -586356 , -601438 , -616337 , -631048 , -645567 , -659890 , -674011 , -687927 , -701634 , -715127 , -728402 , -741455 , -754282 , -766879 , -779243 , -791370 ,
                        -803255 , -814896 , -826289 , -837430 , -848315 , -858943 , -869308 , -879409 , -889242 , -898805 , -908093 , -917105 , -925837 , -934288 , -942453 , -950332 , -957921 , -965219 , -972222 , -978930 ,
                        -985339 , -991448 , -997255 ,-1002758 ,-1007955 ,-1012846 ,-1017428 ,-1021701 ,-1025662 ,-1029310 ,-1032645 ,-1035666 ,-1038371 ,-1040760 ,-1042831 ,-1044585 ,-1046021 ,-1047138 ,-1047937 ,-1048416 ,
                       -1048576};
//map sinX' value (X range from -180' to 180') to CSC_sin[0 ... 360]
CBIOS_S32  CSC_sin[] = {0 ,  -18300 ,  -36594 ,  -54878 ,  -73144 ,  -91389 , -109606 , -127789 , -145933 , -164033 , -182083 , -200077 , -218011 , -235878 , -253673 , -271391 , -289026 , -306573 , -324027 , -341382 ,
                  -358634 , -375776 , -392803 , -409711 , -426494 , -443147 , -459665 , -476043 , -492276 , -508359 , -524287 , -540056 , -555660 , -571095 , -586356 , -601438 , -616337 , -631048 , -645567 , -659890 ,
                  -674011 , -687927 , -701634 , -715127 , -728402 , -741455 , -754282 , -766879 , -779243 , -791370 , -803255 , -814896 , -826289 , -837430 , -848315 , -858943 , -869308 , -879409 , -889242 , -898805 ,
                  -908093 , -917105 , -925837 , -934288 , -942453 , -950332 , -957921 , -965219 , -972222 , -978930 , -985339 , -991448 , -997255 ,-1002758 ,-1007955 ,-1012846 ,-1017428 ,-1021701 ,-1025662 ,-1029310 ,
                 -1032645 ,-1035666 ,-1038371 ,-1040760 ,-1042831 ,-1044585 ,-1046021 ,-1047138 ,-1047937 ,-1048416 ,-1048576 ,-1048416 ,-1047937 ,-1047138 ,-1046021 ,-1044585 ,-1042831 ,-1040760 ,-1038371 ,-1035666 ,
                 -1032645 ,-1029310 ,-1025662 ,-1021701 ,-1017428 ,-1012846 ,-1007955 ,-1002758 , -997255 , -991448 , -985339 , -978930 , -972222 , -965219 , -957921 , -950332 , -942453 , -934288 , -925837 , -917105 ,
                  -908093 , -898805 , -889242 , -879409 , -869308 , -858943 , -848315 , -837430 , -826289 , -814896 , -803255 , -791370 , -779243 , -766879 , -754282 , -741455 , -728402 , -715127 , -701634 , -687927 ,
                  -674011 , -659890 , -645567 , -631048 , -616337 , -601438 , -586356 , -571095 , -555660 , -540056 , -524288 , -508359 , -492276 , -476043 , -459665 , -443147 , -426494 , -409711 , -392803 , -375776 ,
                  -358634 , -341382 , -324027 , -306573 , -289026 , -271391 , -253673 , -235878 , -218011 , -200077 , -182083 , -164033 , -145933 , -127789 , -109606 ,  -91389 ,  -73144 ,  -54878 ,  -36594 ,  -18300 ,
                        0 ,   18300 ,   36594 ,   54878 ,   73144 ,   91389 ,  109606 ,  127789 ,  145933 ,  164033 ,  182083 ,  200077 ,  218011 ,  235878 ,  253673 ,  271391 ,  289026 ,  306573 ,  324027 ,  341382 ,
                   358634 ,  375776 ,  392803 ,  409711 ,  426494 ,  443147 ,  459665 ,  476043 ,  492276 ,  508359 ,  524288 ,  540056 ,  555660 ,  571095 ,  586356 ,  601438 ,  616337 ,  631048 ,  645567 ,  659890 ,
                   674011 ,  687927 ,  701634 ,  715127 ,  728402 ,  741455 ,  754282 ,  766879 ,  779243 ,  791370 ,  803255 ,  814896 ,  826289 ,  837430 ,  848315 ,  858943 ,  869308 ,  879409 ,  889242 ,  898805 ,
                   908093 ,  917105 ,  925837 ,  934288 ,  942453 ,  950332 ,  957921 ,  965219 ,  972222 ,  978930 ,  985339 ,  991448 ,  997255 , 1002758 , 1007955 , 1012846 , 1017428 , 1021701 , 1025662 , 1029310 ,
                  1032645 , 1035666 , 1038371 , 1040760 , 1042831 , 1044585 , 1046021 , 1047138 , 1047937 , 1048416 , 1048576 , 1048416 , 1047937 , 1047138 , 1046021 , 1044585 , 1042831 , 1040760 , 1038371 , 1035666 ,
                  1032645 , 1029310 , 1025662 , 1021701 , 1017428 , 1012846 , 1007955 , 1002758 ,  997255 ,  991448 ,  985339 ,  978930 ,  972222 ,  965219 ,  957921 ,  950332 ,  942453 ,  934288 ,  925837 ,  917105 ,
                   908093 ,  898805 ,  889242 ,  879409 ,  869308 ,  858943 ,  848315 ,  837430 ,  826289 ,  814896 ,  803255 ,  791370 ,  779243 ,  766879 ,  754282 ,  741455 ,  728402 ,  715127 ,  701634 ,  687927 ,
                   674011 ,  659890 ,  645567 ,  631048 ,  616337 ,  601438 ,  586356 ,  571095 ,  555660 ,  540056 ,  524287 ,  508359 ,  492276 ,  476043 ,  459665 ,  443147 ,  426494 ,  409711 ,  392803 ,  375776 ,
                   358634 ,  341382 ,  324027 ,  306573 ,  289026 ,  271391 ,  253673 ,  235878 ,  218011 ,  200077 ,  182083 ,  164033 ,  145933 ,  127789 ,  109606 ,   91389 ,   73144 ,   54878 ,   36594 ,   18300 ,
                        0 ,};

