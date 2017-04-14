/* include file fore libparasyte
 */

#ifndef __PARASYTE_H__
#define __PARASYTE_H__

#include <termios.h>
#include <unistd.h>

void init_keyboard(struct termios *saved_settings);
void restore_keyboard(struct termios *saved_settings);

#endif //__PARASYTE_H__
