/*    This file is part of quicky_utils
      Copyright (C) 2018  Julien Thevenon ( julien_thevenon at yahoo.fr )

      This program is free software: you can redistribute it and/or modify
      it under the terms of the GNU General Public License as published by
      the Free Software Foundation, either version 3 of the License, or
      (at your option) any later version.

      This program is distributed in the hope that it will be useful,
      but WITHOUT ANY WARRANTY; without even the implied warranty of
      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
      GNU General Public License for more details.

      You should have received a copy of the GNU General Public License
      along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#ifndef QUICKY_UTILS_PASSWORD_INPUT_H
#define QUICKY_UTILS_PASSWORD_INPUT_H

#ifndef WIN32
#include <unistd.h>     /* getlogin */
#include <termios.h>    /* tcsetattr */
#else
#include <windows.h>    /* DWORD, GetUserName, SetConsoleMode */
#endif // WIN32

#include <string>
#include <iostream>

#ifdef WIN32
char *getlogin(void)
{
    static char user_name[MAX_PATH];
    DWORD  length = sizeof (user_name);
    if (GetUserName (user_name, &length))
        return user_name;
    return NULL;
}
#endif

void set_stdin_echo(bool enable = true)
{
#ifdef WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin, &mode);

    if( !enable )
        mode &= ~ENABLE_ECHO_INPUT;
    else
        mode |= ENABLE_ECHO_INPUT;

    SetConsoleMode(hStdin, mode );
#else

    struct termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable )
        tty.c_lflag &= ~ECHO;
    else
        tty.c_lflag |= ECHO;

    (void) tcsetattr(STDIN_FILENO, TCSANOW, &tty);
#endif
}

void getpass2(std::string & p_passwd, const std::string & p_prompt)
{
  std::cout << p_prompt;
  set_stdin_echo( false);
  std::cin >> p_passwd;
  set_stdin_echo( true);
}

#endif //QUICKY_UTILS_PASSWORD_INPUT_H
//EOF
