/*
 * myutils.h
 *
 * Created: 02-Jun-13 9:30:09 PM
 *  Author: dell
 */ 


#ifndef MYUTILS_H
 #define MYUTILS_H

 #define _CONCAT(a,b) a##b
 #define PORT(x) _CONCAT(PORT,x)
 #define PIN(x) _CONCAT(PIN,x)
 #define DDR(x) _CONCAT(DDR,x)

#endif
