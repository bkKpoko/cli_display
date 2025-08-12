#ifndef _PARAMS_H_
#define _PARAMS_H_

#define PROG_NAME "./main"

#define HORIZONTAL L'═' // 0x2550
#define VERTICAL L'║'   // 0x2551
#define ANGLE_L_T L'╔'  // 0x2554
#define ANGLE_L_B L'╚'  // 0x255A
#define ANGLE_R_B L'╝'  // 0x255D
#define ANGLE_R_T L'╗'  // 0x2557

#define TR_LEFT L'╠'   // 0x2560
#define TR_TOP L'╦'    // 0x2566
#define TR_BOTTOM L'╩' // x25669
#define TR_RIGHT L'╣'  // 0x2563

#define CROSS L'╬' // 0x256C

#define GRAY0 L'·' // 0xB7
#define GRAY1 L'░' // 0x2591
#define GRAY2 L'▒' // 0x2592
#define GRAY3 L'▓' // 0x2593
#define GRAY4 L'█' // 0x2588

#define FONT_ASPECT 0.5

const int WIDTH = 16 * 16;
const int HEIGHT = 9 * 10;

const int GRAYSCALE_SIZE = 18;
const wchar_t GRAYSCALE[GRAYSCALE_SIZE + 1] = L" ·:!/r(l1Z4H9W8$@\x2592";

#endif // !_PARAMS_H_
