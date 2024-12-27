#ifndef PROMPT_H
#define PROMPT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

static char* currDir;

void prompt_yazdir();
void quit();
void cd();
int tekli_komut();
int komut_yurutucu();

#endif