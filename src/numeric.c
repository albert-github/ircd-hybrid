/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  numeric.c: Numeric handling functions.
 *
 *  Copyright (C) 2002 by the past and present ircd coders, and others.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 *  USA
 *
 *  $Id$
 */

#include "stdinc.h"
#include "numeric.h"


static const char *replies[] = {
/* 000 */ NULL,
/* 001 RPL_WELCOME */ ":%s 001 %s :Welcome to the %s Internet Relay Chat Network %s!%s@%s",
/* 002 RPL_YOURHOST */ ":%s 002 %s :Your host is %s, running version %s",
/* 003 RPL_CREATED */ ":%s 003 %s :This server was created %s",
/* 004 RPL_MYINFO */ ":%s 004 %s %s %s %s bciklmnoprstveIMORS bkloveI",
/* 005 RPL_ISUPPORT */ ":%s 005 %s %s :are supported by this server",
/* 006 */ NULL,
/* 007 */ NULL,
/* 008 */ NULL,
/* 009 */ NULL,
/* 010 RPL_REDIR */ ":%s 010 %s %s %u :Please use this Server/Port instead",
/* 011 */ NULL,
/* 012 */ NULL,
/* 013 */ NULL,
/* 014 */ NULL,
/* 015 RPL_MAP */ ":%s 015 %s :%s%s%s [%u clients] (%u%%)",
/* 016 RPL_MAPMORE */ ":%s 016 %s :%s%s --> *more*",
/* 017 RPL_MAPEND */ ":%s 017 %s :End of /MAP",
/* 018 */ NULL,
/* 019 */ NULL,
/* 020 */ NULL,
/* 021 */ NULL,
/* 022 */ NULL,
/* 023 */ NULL,
/* 024 */ NULL,
/* 025 */ NULL,
/* 026 */ NULL,
/* 027 */ NULL,
/* 028 */ NULL,
/* 029 */ NULL,
/* 030 */ NULL,
/* 031 */ NULL,
/* 032 */ NULL,
/* 033 */ NULL,
/* 034 */ NULL,
/* 035 */ NULL,
/* 036 */ NULL,
/* 037 */ NULL,
/* 038 */ NULL,
/* 039 */ NULL,
/* 040 */ NULL,
/* 041 */ NULL,
/* 042 RPL_YOURID */ ":%s 042 %s %s :your unique ID",
/* 043 */ NULL,
/* 044 */ NULL,
/* 045 */ NULL,
/* 046 */ NULL,
/* 047 */ NULL,
/* 048 */ NULL,
/* 049 */ NULL,
/* 050 */ NULL,
/* 051 */ NULL,
/* 052 */ NULL,
/* 053 */ NULL,
/* 054 */ NULL,
/* 055 */ NULL,
/* 056 */ NULL,
/* 057 */ NULL,
/* 058 */ NULL,
/* 059 */ NULL,
/* 060 */ NULL,
/* 061 */ NULL,
/* 062 */ NULL,
/* 063 */ NULL,
/* 064 */ NULL,
/* 065 */ NULL,
/* 066 */ NULL,
/* 067 */ NULL,
/* 068 */ NULL,
/* 069 */ NULL,
/* 070 */ NULL,
/* 071 */ NULL,
/* 072 */ NULL,
/* 073 */ NULL,
/* 074 */ NULL,
/* 075 */ NULL,
/* 076 */ NULL,
/* 077 */ NULL,
/* 078 */ NULL,
/* 079 */ NULL,
/* 080 */ NULL,
/* 081 */ NULL,
/* 082 */ NULL,
/* 083 */ NULL,
/* 084 */ NULL,
/* 085 */ NULL,
/* 086 */ NULL,
/* 087 */ NULL,
/* 088 */ NULL,
/* 089 */ NULL,
/* 090 */ NULL,
/* 091 */ NULL,
/* 092 */ NULL,
/* 093 */ NULL,
/* 094 */ NULL,
/* 095 */ NULL,
/* 096 */ NULL,
/* 097 */ NULL,
/* 098 */ NULL,
/* 099 */ NULL,
/* 100 */ NULL,
/* 101 */ NULL,
/* 102 */ NULL,
/* 103 */ NULL,
/* 104 */ NULL,
/* 105 */ NULL,
/* 106 */ NULL,
/* 107 */ NULL,
/* 108 */ NULL,
/* 109 */ NULL,
/* 110 */ NULL,
/* 111 */ NULL,
/* 112 */ NULL,
/* 113 */ NULL,
/* 114 */ NULL,
/* 115 */ NULL,
/* 116 */ NULL,
/* 117 */ NULL,
/* 118 */ NULL,
/* 119 */ NULL,
/* 120 */ NULL,
/* 121 */ NULL,
/* 122 */ NULL,
/* 123 */ NULL,
/* 124 */ NULL,
/* 125 */ NULL,
/* 126 */ NULL,
/* 127 */ NULL,
/* 128 */ NULL,
/* 129 */ NULL,
/* 130 */ NULL,
/* 131 */ NULL,
/* 132 */ NULL,
/* 133 */ NULL,
/* 134 */ NULL,
/* 135 */ NULL,
/* 136 */ NULL,
/* 137 */ NULL,
/* 138 */ NULL,
/* 139 */ NULL,
/* 140 */ NULL,
/* 141 */ NULL,
/* 142 */ NULL,
/* 143 */ NULL,
/* 144 */ NULL,
/* 145 */ NULL,
/* 146 */ NULL,
/* 147 */ NULL,
/* 148 */ NULL,
/* 149 */ NULL,
/* 150 */ NULL,
/* 151 */ NULL,
/* 152 */ NULL,
/* 153 */ NULL,
/* 154 */ NULL,
/* 155 */ NULL,
/* 156 */ NULL,
/* 157 */ NULL,
/* 158 */ NULL,
/* 159 */ NULL,
/* 160 */ NULL,
/* 161 */ NULL,
/* 162 */ NULL,
/* 163 */ NULL,
/* 164 */ NULL,
/* 165 */ NULL,
/* 166 */ NULL,
/* 167 */ NULL,
/* 168 */ NULL,
/* 169 */ NULL,
/* 170 */ NULL,
/* 171 */ NULL,
/* 172 */ NULL,
/* 173 */ NULL,
/* 174 */ NULL,
/* 175 */ NULL,
/* 176 */ NULL,
/* 177 */ NULL,
/* 178 */ NULL,
/* 179 */ NULL,
/* 180 */ NULL,
/* 181 */ NULL,
/* 182 */ NULL,
/* 183 */ NULL,
/* 184 */ NULL,
/* 185 */ NULL,
/* 186 */ NULL,
/* 187 */ NULL,
/* 188 */ NULL,
/* 189 */ NULL,
/* 190 */ NULL,
/* 191 */ NULL,
/* 192 */ NULL,
/* 193 */ NULL,
/* 194 */ NULL,
/* 195 */ NULL,
/* 196 */ NULL,
/* 197 */ NULL,
/* 198 */ NULL,
/* 199 */ NULL,
/* 200 RPL_TRACELINK */ ":%s 200 %s Link %s %s %s",
/* 201 RPL_TRACECONNECTING */ ":%s 201 %s Try. %s %s",
/* 202 RPL_TRACEHANDSHAKE */ ":%s 202 %s H.S. %s %s",
/* 203 RPL_TRACEUNKNOWN */ ":%s 203 %s ???? %s %s (%s) %d",
/* 204 RPL_TRACEOPERATOR */ ":%s 204 %s Oper %s %s (%s) %lu %u",
/* 205 RPL_TRACEUSER */ ":%s 205 %s User %s %s (%s) %lu %u",
/* 206 RPL_TRACESERVER */ ":%s 206 %s Serv %s %dS %dC %s %s!%s@%s %lu",
/* 207 */ NULL,
/* 208 RPL_TRACENEWTYPE */ ":%s 208 %s <newtype> 0 %s",
/* 209 RPL_TRACECLASS */ ":%s 209 %s Class %s %d",
/* 210 */ NULL,
/* 211 RPL_STATSLINKINFO */ ":%s 211 %s %s %u %u %llu %u %llu :%u %u %s",
/* 212 RPL_STATSCOMMANDS */ ":%s 212 %s %s %u %llu :%u",
/* 213 RPL_STATSCLINE */ ":%s 213 %s %c %s %s %s %d %s",
/* 214 RPL_STATSNLINE */ ":%s 214 %s %c %s * %s %d %s",
/* 215 RPL_STATSILINE */ ":%s 215 %s %c %s * %s@%s %d %s",
/* 216 RPL_STATSKLINE */ ":%s 216 %s %c %s * %s :%s",
/* 217 RPL_STATSQLINE */ ":%s 217 %s %c %u %s :%s",
/* 218 RPL_STATSYLINE */ ":%s 218 %s %c %s %u %u %u %u %u %u %u/%u %u/%u %s",
/* 219 RPL_ENDOFSTATS */ ":%s 219 %s %c :End of /STATS report",
/* 220 RPL_STATSPLINE */ ":%s 220 %s %c %d %s %d %s :%s",
/* 221 RPL_UMODEIS */ ":%s 221 %s %s",
/* 222 */ NULL,
/* 223 */ NULL,
/* 224 */ NULL,
/* 225 RPL_STATSDLINE */ ":%s 225 %s %c %s :%s",
/* 226 RPL_STATSALINE */ ":%s 226 %s %s",
/* 227 */ NULL,
/* 228 */ NULL,
/* 229 */ NULL,
/* 230 */ NULL,
/* 231 */ NULL,
/* 232 */ NULL,
/* 233 */ NULL,
/* 234 */ NULL,
/* 235 */ NULL,
/* 236 */ NULL,
/* 237 */ NULL,
/* 238 */ NULL,
/* 239 */ NULL,
/* 240 */ NULL,
/* 241 RPL_STATSLLINE */ ":%s 241 %s %c %s * %s %d %s",
/* 242 RPL_STATSUPTIME */ ":%s 242 %s :Server Up %d days, %d:%02d:%02d",
/* 243 RPL_STATSOLINE */ ":%s 243 %s %c %u %s@%s * %s %s %s",
/* 244 RPL_STATSHLINE */ ":%s 244 %s %c %s * %s %d %s",
/* 245 */ NULL,
/* 246 RPL_STATSSERVICE */ ":%s 246 %s %c %s * %s %d %d",
/* 247 RPL_STATSXLINE */ ":%s 247 %s %c %d %s :%s",
/* 248 RPL_STATSULINE */ ":%s 248 %s U %s %s@%s %s",
/* 249 */ NULL,
/* 250 RPL_STATSCONN */ ":%s 250 %s :Highest connection count: %d (%d clients) (%llu connections received)",
/* 251 RPL_LUSERCLIENT */ ":%s 251 %s :There are %d users and %d invisible on %d servers",
/* 252 RPL_LUSEROP */ ":%s 252 %s %d :IRC Operators online",
/* 253 RPL_LUSERUNKNOWN */ ":%s 253 %s %d :unknown connection(s)",
/* 254 RPL_LUSERCHANNELS */ ":%s 254 %s %d :channels formed",
/* 255 RPL_LUSERME */ ":%s 255 %s :I have %d clients and %d servers",
/* 256 RPL_ADMINME */ ":%s 256 %s :Administrative info about %s",
/* 257 RPL_ADMINLOC1 */ ":%s 257 %s :%s",
/* 258 RPL_ADMINLOC2 */ ":%s 258 %s :%s",
/* 259 RPL_ADMINEMAIL */ ":%s 259 %s :%s",
/* 260 */ NULL,
/* 261 */ NULL,
/* 262 RPL_ENDOFTRACE */ ":%s 262 %s %s :End of TRACE",
/* 263 RPL_LOAD2HI */ ":%s 263 %s :Server load is temporarily too heavy. Please wait a while and try again.",
/* 264 */ NULL,
/* 265 RPL_LOCALUSERS */ ":%s 265 %s :Current local users: %d  Max: %d",
/* 266 RPL_GLOBALUSERS */ ":%s 266 %s :Current global users: %d  Max: %d",
/* 267 */ NULL,
/* 268 */ NULL,
/* 269 */ NULL,
/* 270 */ NULL,
/* 271 */ NULL,
/* 272 */ NULL,
/* 273 */ NULL,
/* 274 */ NULL,
/* 275 */ NULL,
/* 276 */ NULL,
/* 277 */ NULL,
/* 278 */ NULL,
/* 279 */ NULL,
/* 280 */ NULL,
/* 281 RPL_ACCEPTLIST */ ":%s 281 %s :%s",
/* 282 RPL_ENDOFACCEPT */ ":%s 282 %s :End of /ACCEPT list.",
/* 283 */ NULL,
/* 284 */ NULL,
/* 285 */ NULL,
/* 286 */ NULL,
/* 287 */ NULL,
/* 288 */ NULL,
/* 289 */ NULL,
/* 290 */ NULL,
/* 291 */ NULL,
/* 292 */ NULL,
/* 293 */ NULL,
/* 294 */ NULL,
/* 295 */ NULL,
/* 296 */ NULL,
/* 297 */ NULL,
/* 298 */ NULL,
/* 299 */ NULL,
/* 300 */ NULL,
/* 301 RPL_AWAY */ ":%s 301 %s %s :%s",
/* 302 RPL_USERHOST */ ":%s 302 %s :%s",
/* 303 RPL_ISON */ ":%s 303 %s :",
/* 304 */ NULL,
/* 305 RPL_UNAWAY */ ":%s 305 %s :You are no longer marked as being away",
/* 306 RPL_NOWAWAY */ ":%s 306 %s :You have been marked as being away",
/* 307 RPL_WHOISREGNICK */ ":%s 307 %s %s :has identified for this nick",
/* 308 RPL_WHOISADMIN */ ":%s 313 %s %s :is a Server Administrator",
/* 309 */ NULL,
/* 310 */ NULL,
/* 311 RPL_WHOISUSER */ ":%s 311 %s %s %s %s * :%s",
/* 312 RPL_WHOISSERVER */ ":%s 312 %s %s %s :%s",
/* 313 RPL_WHOISOPERATOR */ ":%s 313 %s %s :is an IRC Operator",
/* 314 RPL_WHOWASUSER */ ":%s 314 %s %s %s %s * :%s",
/* 315 RPL_ENDOFWHO */ ":%s 315 %s %s :End of /WHO list.",
/* 316 */ NULL,
/* 317 RPL_WHOISIDLE */ ":%s 317 %s %s %u %d :seconds idle, signon time",
/* 318 RPL_ENDOFWHOIS */ ":%s 318 %s %s :End of /WHOIS list.",
/* 319 RPL_WHOISCHANNELS */ ":%s 319 %s %s :%s",
/* 320 */ NULL,
/* 321 RPL_LISTSTART */ ":%s 321 %s Channel :Users  Name",
/* 322 RPL_LIST */ ":%s 322 %s %s %d :%s",
/* 323 RPL_LISTEND */ ":%s 323 %s :End of /LIST",
/* 324 RPL_CHANNELMODEIS */ ":%s 324 %s %s %s %s",
/* 325 */ NULL,
/* 326 */ NULL,
/* 327 */ NULL,
/* 328 */ NULL,
/* 329 RPL_CREATIONTIME */ ":%s 329 %s %s %lu",
/* 330 */ NULL,
/* 331 RPL_NOTOPIC */ ":%s 331 %s %s :No topic is set.",
/* 332 RPL_TOPIC */ ":%s 332 %s %s :%s",
/* 333 RPL_TOPICWHOTIME */ ":%s 333 %s %s %s %lu",
/* 334 */ NULL,
/* 335 */ NULL,
/* 336 */ NULL,
/* 337 */ NULL,
/* 338 RPL_WHOISACTUALLY */ ":%s 338 %s %s %s :actually using host",
/* 339 */ NULL,
/* 340 */ NULL,
/* 341 RPL_INVITING */ ":%s 341 %s %s %s",
/* 342 */ NULL,
/* 343 */ NULL,
/* 344 */ NULL,
/* 345 */ NULL,
/* 346 RPL_INVEXLIST */ ":%s 346 %s %s %s!%s@%s %s %lu",
/* 347 RPL_ENDOFINVEXLIST */ ":%s 347 %s %s :End of Channel Invite List",
/* 348 RPL_EXCEPTLIST */ ":%s 348 %s %s %s!%s@%s %s %lu",
/* 349 RPL_ENDOFEXCEPTLIST */ ":%s 349 %s %s :End of Channel Exception List",
/* 350 */ NULL,
/* 351 RPL_VERSION */ ":%s 351 %s %s(%s). %s :%s%s",
/* 352 RPL_WHOREPLY */ ":%s 352 %s %s %s %s %s %s %s :%d %s",
/* 353 RPL_NAMREPLY */ ":%s 353 %s %s %s :",
/* 354 */ NULL,
/* 355 */ NULL,
/* 356 */ NULL,
/* 357 */ NULL,
/* 358 */ NULL,
/* 359 */ NULL,
/* 360 */ NULL,
/* 361 */ NULL,
/* 362 RPL_CLOSING */ ":%s 362 %s %s :Closed. Status = %d",
/* 363 RPL_CLOSEEND */ ":%s 363 %s %d: Connections Closed",
/* 364 RPL_LINKS */ ":%s 364 %s %s %s :%d %s",
/* 365 RPL_ENDOFLINKS */ ":%s 365 %s %s :End of /LINKS list.",
/* 366 RPL_ENDOFNAMES */ ":%s 366 %s %s :End of /NAMES list.",
/* 367 RPL_BANLIST */ ":%s 367 %s %s %s!%s@%s %s %lu",
/* 368 RPL_ENDOFBANLIST */ ":%s 368 %s %s :End of Channel Ban List",
/* 369 RPL_ENDOFWHOWAS */ ":%s 369 %s %s :End of WHOWAS",
/* 370 */ NULL,
/* 371 RPL_INFO */ ":%s 371 %s :%s",
/* 372 RPL_MOTD */ ":%s 372 %s :- %s",
/* 373 RPL_INFOSTART */ ":%s 373 %s :Server INFO",
/* 374 RPL_ENDOFINFO */ ":%s 374 %s :End of /INFO list.",
/* 375 RPL_MOTDSTART */ ":%s 375 %s :- %s Message of the Day - ",
/* 376 RPL_ENDOFMOTD */ ":%s 376 %s :End of /MOTD command.",
/* 377 */ NULL,
/* 378 */ NULL,
/* 379 */ NULL,
/* 380 */ NULL,
/* 381 RPL_YOUREOPER */ ":%s 381 %s :You have entered... the Twilight Zone!",
/* 382 RPL_REHASHING */ ":%s 382 %s %s :Rehashing",
/* 383 */ NULL,
/* 384 */ NULL,
/* 385 */ NULL,
/* 386 RPL_RSACHALLENGE */ ":%s 386 %s :%s",
/* 387 */ NULL,
/* 388 */ NULL,
/* 389 */ NULL,
/* 390 */ NULL,
/* 391 RPL_TIME */ ":%s 391 %s %s :%s",
/* 392 */ NULL,
/* 393 */ NULL,
/* 394 */ NULL,
/* 395 */ NULL,
/* 396 */ NULL,
/* 397 */ NULL,
/* 398 */ NULL,
/* 399 */ NULL,
/* 400 */ NULL,
/* 401 ERR_NOSUCHNICK */ ":%s 401 %s %s :No such nick/channel",
/* 402 ERR_NOSUCHSERVER */ ":%s 402 %s %s :No such server",
/* 403 ERR_NOSUCHCHANNEL */ ":%s 403 %s %s :No such channel",
/* 404 ERR_CANNOTSENDTOCHAN */ ":%s 404 %s %s :Cannot send to channel",
/* 405 ERR_TOOMANYCHANNELS */ ":%s 405 %s %s :You have joined too many channels",
/* 406 ERR_WASNOSUCHNICK */ ":%s 406 %s %s :There was no such nickname",
/* 407 ERR_TOOMANYTARGETS */ ":%s 407 %s %s :Too many recipients. Only %d processed",
/* 408 ERR_NOCTRLSONCHAN*/ ":%s 408 %s %s :You cannot use control codes on this channel. Not sent: %s",
/* 409 ERR_NOORIGIN */ ":%s 409 %s :No origin specified",
/* 410 ERR_INVALIDCAPCMD */ ":%s 410 %s %s :Invalid CAP subcommand",
/* 411 ERR_NORECIPIENT */ ":%s 411 %s :No recipient given (%s)",
/* 412 ERR_NOTEXTTOSEND */ ":%s 412 %s :No text to send",
/* 413 ERR_NOTOPLEVEL */ ":%s 413 %s %s :No toplevel domain specified",
/* 414 ERR_WILDTOPLEVEL */ ":%s 414 %s %s :Wildcard in toplevel Domain",
/* 415 */ NULL,
/* 416 */ NULL,
/* 417 */ NULL,
/* 418 */ NULL,
/* 419 */ NULL,
/* 420 */ NULL,
/* 421 ERR_UNKNOWNCOMMAND */ ":%s 421 %s %s :Unknown command",
/* 422 ERR_NOMOTD */ ":%s 422 %s :MOTD File is missing",
/* 423 ERR_NOADMININFO */ ":%s 423 %s %s :No administrative info available",
/* 424 */ NULL,
/* 425 */ NULL,
/* 426 */ NULL,
/* 427 */ NULL,
/* 428 */ NULL,
/* 429 */ NULL,
/* 430 */ NULL,
/* 431 ERR_NONICKNAMEGIVEN */ ":%s 431 %s :No nickname given",
/* 432 ERR_ERRONEUSNICKNAME */ ":%s 432 %s %s :%s",
/* 433 ERR_NICKNAMEINUSE */ ":%s 433 %s %s :Nickname is already in use.",
/* 434 */ NULL,
/* 435 */ NULL,
/* 436 ERR_NICKCOLLISION */ ":%s 436 %s %s :Nickname collision KILL",
/* 437 ERR_UNAVAILRESOURCE */ ":%s 437 %s %s :Nick/channel is temporarily unavailable",
/* 438 ERR_NICKTOOFAST */ ":%s 438 %s %s %s :Nick change too fast. Please wait %d seconds.",
/* 439 */ NULL,
/* 440 ERR_SERVICESDOWN */ ":%s 440 %s %s :Services is currently down.",
/* 441 ERR_USERNOTINCHANNEL */ ":%s 441 %s %s %s :They aren't on that channel",
/* 442 ERR_NOTONCHANNEL */ ":%s 442 %s %s :You're not on that channel",
/* 443 ERR_USERONCHANNEL */ ":%s 443 %s %s %s :is already on channel",
/* 444 */ NULL,
/* 445 */ NULL,
/* 446 */ NULL,
/* 447 */ NULL,
/* 448 */ NULL,
/* 449 */ NULL,
/* 450 */ NULL,
/* 451 ERR_NOTREGISTERED */ ":%s 451 %s :You have not registered",
/* 452 */ NULL,
/* 453 */ NULL,
/* 454 */ NULL,
/* 455 */ NULL,
/* 456 ERR_ACCEPTFULL */ ":%s 456 %s :Accept list is full",
/* 457 ERR_ACCEPTEXIST */ ":%s 457 %s %s!%s@%s :is already on your accept list",
/* 458 ERR_ACCEPTNOT */ ":%s 458 %s %s!%s@%s :is not on your accept list",
/* 459 */ NULL,
/* 460 */ NULL,
/* 461 ERR_NEEDMOREPARAMS */ ":%s 461 %s %s :Not enough parameters",
/* 462 ERR_ALREADYREGISTRED */ ":%s 462 %s :You may not reregister",
/* 463 */ NULL,
/* 464 ERR_PASSWDMISMATCH */ ":%s 464 %s :Password Incorrect",
/* 465 ERR_YOUREBANNEDCREEP */ ":%s 465 %s :You are banned from this server- %s",
/* 466 */ NULL,
/* 467 */ NULL,
/* 468 ERR_ONLYSERVERSCANCHANGE */ ":%s 468 %s %s :Only servers can change that mode",
/* 469 */ NULL,
/* 470 ERR_OPERONLYCHAN */ ":%s 470 %s %s :Cannot join channel (+O)",
/* 471 ERR_CHANNELISFULL */ ":%s 471 %s %s :Cannot join channel (+l)",
/* 472 ERR_UNKNOWNMODE */ ":%s 472 %s %c :is unknown mode char to me",
/* 473 ERR_INVITEONLYCHAN */ ":%s 473 %s %s :Cannot join channel (+i)",
/* 474 ERR_BANNEDFROMCHAN */ ":%s 474 %s %s :Cannot join channel (+b)",
/* 475 ERR_BADCHANNELKEY */ ":%s 475 %s %s :Cannot join channel (+k)",
/* 476 */ NULL,
/* 477 ERR_NEEDREGGEDNICK */ ":%s 477 %s %s :You need to identify to a registered nick to join or speak in that channel.",
/* 478 ERR_BANLISTFULL */ ":%s 478 %s %s %s :Channel ban list is full",
/* 479 ERR_BADCHANNAME */ ":%s 479 %s %s :Illegal channel name",
/* 480 ERR_SSLONLYCHAN */ ":%s 480 %s %s :Cannot join channel (+S)",
/* 481 ERR_NOPRIVILEGES */ ":%s 481 %s :Permission Denied - You're not an IRC operator",
/* 482 ERR_CHANOPRIVSNEEDED */ ":%s 482 %s %s :You're not channel operator",
/* 483 ERR_CANTKILLSERVER */ ":%s 483 %s :You can't kill a server!",
/* 484 ERR_RESTRICTED */ ":%s 484 %s :You are restricted",
/* 485 ERR_CHANBANREASON */ ":%s 485 %s %s :Cannot join channel (%s)",
/* 486 ERR_NONONREG */ ":%s 486 %s %s :You must identify to a registered nick to private message that person",
/* 487 */ NULL,
/* 488 */ NULL,
/* 489 */ NULL,
/* 490 */ NULL,
/* 491 ERR_NOOPERHOST */ ":%s 491 %s :Only few of mere mortals may try to enter the twilight zone",
/* 492 */ NULL,
/* 493 */ NULL,
/* 494 */ NULL,
/* 495 */ NULL,
/* 496 */ NULL,
/* 497 */ NULL,
/* 498 */ NULL,
/* 499 */ NULL,
/* 500 */ NULL,
/* 501 ERR_UMODEUNKNOWNFLAG */ ":%s 501 %s :Unknown MODE flag",
/* 502 ERR_USERSDONTMATCH */ ":%s 502 %s :Can't change mode for other users",
/* 503 ERR_GHOSTEDCLIENT */ ":%s 503 %s :Message could not be delivered to %s",
/* 504 ERR_USERNOTONSERV */ ":%s 504 %s %s :User is not on this server",
/* 505 */ NULL,
/* 506 */ NULL,
/* 507 */ NULL,
/* 508 */ NULL,
/* 509 */ NULL,
/* 510 */ NULL,
/* 511 */ NULL,
/* 512 ERR_TOOMANYWATCH */ ":%s 512 %s %s :Maximum size for WATCH-list is %d entries",
/* 513 ERR_WRONGPONG */ ":%s 513 %s :To connect type /QUOTE PONG %u",
/* 514 */ NULL,
/* 515 */ NULL,
/* 516 */ NULL,
/* 517 */ NULL,
/* 518 */ NULL,
/* 519 */ NULL,
/* 520 */ NULL,
/* 521 ERR_LISTSYNTAX */ ":%s 521 %s :Bad list syntax, type /QUOTE HELP LIST",
/* 522 */ NULL,
/* 523 */ NULL,
/* 524 ERR_HELPNOTFOUND */ ":%s 524 %s %s :Help not found",
/* 525 */ NULL,
/* 526 */ NULL,
/* 527 */ NULL,
/* 528 */ NULL,
/* 529 */ NULL,
/* 530 */ NULL,
/* 531 */ NULL,
/* 532 */ NULL,
/* 533 */ NULL,
/* 534 */ NULL,
/* 535 */ NULL,
/* 536 */ NULL,
/* 537 */ NULL,
/* 538 */ NULL,
/* 539 */ NULL,
/* 540 */ NULL,
/* 541 */ NULL,
/* 542 */ NULL,
/* 543 */ NULL,
/* 544 */ NULL,
/* 545 */ NULL,
/* 546 */ NULL,
/* 547 */ NULL,
/* 548 */ NULL,
/* 549 */ NULL,
/* 550 */ NULL,
/* 551 */ NULL,
/* 552 */ NULL,
/* 553 */ NULL,
/* 554 */ NULL,
/* 555 */ NULL,
/* 556 */ NULL,
/* 557 */ NULL,
/* 558 */ NULL,
/* 559 */ NULL,
/* 560 */ NULL,
/* 561 */ NULL,
/* 562 */ NULL,
/* 563 */ NULL,
/* 564 */ NULL,
/* 565 */ NULL,
/* 566 */ NULL,
/* 567 */ NULL,
/* 568 */ NULL,
/* 569 */ NULL,
/* 570 */ NULL,
/* 571 */ NULL,
/* 572 */ NULL,
/* 573 */ NULL,
/* 574 */ NULL,
/* 575 */ NULL,
/* 576 */ NULL,
/* 577 */ NULL,
/* 578 */ NULL,
/* 579 */ NULL,
/* 580 */ NULL,
/* 581 */ NULL,
/* 582 */ NULL,
/* 583 */ NULL,
/* 584 */ NULL,
/* 585 */ NULL,
/* 586 */ NULL,
/* 587 */ NULL,
/* 588 */ NULL,
/* 589 */ NULL,
/* 590 */ NULL,
/* 591 */ NULL,
/* 592 */ NULL,
/* 593 */ NULL,
/* 594 */ NULL,
/* 595 */ NULL,
/* 596 */ NULL,
/* 597 */ NULL,
/* 598 */ NULL,
/* 599 */ NULL,
/* 600 RPL_LOGON */ ":%s 600 %s %s %s %s %d :logged online",
/* 601 RPL_LOGOFF */ ":%s 601 %s %s %s %s %d :logged offline",
/* 602 RPL_WATCHOFF */ ":%s 602 %s %s %s %s %d :stopped watching",
/* 603 RPL_WATCHSTAT */ ":%s 603 %s :You have %u and are on %u WATCH entries",
/* 604 RPL_NOWON */ ":%s 604 %s %s %s %s %d :is online",
/* 605 RPL_NOWOFF */ ":%s 605 %s %s %s %s %d :is offline",
/* 606 RPL_WATCHLIST */ ":%s 606 %s :%s",
/* 607 RPL_ENDOFWATCHLIST */ ":%s 607 %s :End of WATCH %c",
/* 608 */ NULL,
/* 609 */ NULL,
/* 610 */ NULL,
/* 611 */ NULL,
/* 612 */ NULL,
/* 613 */ NULL,
/* 614 */ NULL,
/* 615 */ NULL,
/* 616 */ NULL,
/* 617 */ NULL,
/* 618 */ NULL,
/* 619 */ NULL,
/* 620 */ NULL,
/* 621 */ NULL,
/* 622 */ NULL,
/* 623 */ NULL,
/* 624 */ NULL,
/* 625 */ NULL,
/* 626 */ NULL,
/* 627 */ NULL,
/* 628 */ NULL,
/* 629 */ NULL,
/* 630 */ NULL,
/* 631 */ NULL,
/* 632 */ NULL,
/* 633 */ NULL,
/* 634 */ NULL,
/* 635 */ NULL,
/* 636 */ NULL,
/* 637 */ NULL,
/* 638 */ NULL,
/* 639 */ NULL,
/* 640 */ NULL,
/* 641 */ NULL,
/* 642 */ NULL,
/* 643 */ NULL,
/* 644 */ NULL,
/* 645 */ NULL,
/* 646 */ NULL,
/* 647 */ NULL,
/* 648 */ NULL,
/* 649 */ NULL,
/* 650 */ NULL,
/* 651 */ NULL,
/* 652 */ NULL,
/* 653 */ NULL,
/* 654 */ NULL,
/* 655 */ NULL,
/* 656 */ NULL,
/* 657 */ NULL,
/* 658 */ NULL,
/* 659 */ NULL,
/* 660 */ NULL,
/* 661 */ NULL,
/* 662 */ NULL,
/* 663 */ NULL,
/* 664 */ NULL,
/* 665 */ NULL,
/* 666 */ NULL,
/* 667 */ NULL,
/* 668 */ NULL,
/* 669 */ NULL,
/* 670 */ NULL,
/* 671 RPL_WHOISSECURE */ ":%s 671 %s %s :is connected via SSL (secure link)",
/* 672 */ NULL,
/* 673 */ NULL,
/* 674 */ NULL,
/* 675 */ NULL,
/* 676 */ NULL,
/* 677 */ NULL,
/* 678 */ NULL,
/* 679 */ NULL,
/* 680 */ NULL,
/* 681 */ NULL,
/* 682 */ NULL,
/* 683 */ NULL,
/* 684 */ NULL,
/* 685 */ NULL,
/* 686 */ NULL,
/* 687 */ NULL,
/* 688 */ NULL,
/* 689 */ NULL,
/* 690 */ NULL,
/* 691 */ NULL,
/* 692 */ NULL,
/* 693 */ NULL,
/* 694 */ NULL,
/* 695 */ NULL,
/* 696 */ NULL,
/* 697 */ NULL,
/* 698 */ NULL,
/* 699 */ NULL,
/* 700 */ NULL,
/* 701 */ NULL,
/* 702 RPL_MODLIST */ ":%s 702 %s %s %p %s %s",
/* 703 RPL_ENDOFMODLIST */ ":%s 703 %s :End of /MODLIST.",
/* 704 RPL_HELPSTART */ ":%s 704 %s %s :%s",
/* 705 RPL_HELPTXT */ ":%s 705 %s %s :%s",
/* 706 RPL_ENDOFHELP */ ":%s 706 %s %s :End of /HELP.",
/* 707 */ NULL,
/* 708 RPL_ETRACE_FULL */ ":%s 708 %s %s %s %s %s %s %s %s %s :%s",
/* 709 RPL_ETRACE */ ":%s 709 %s %s %s %s %s %s %s :%s",
/* 710 RPL_KNOCK */ ":%s 710 %s %s %s!%s@%s :has asked for an invite.",
/* 711 RPL_KNOCKDLVR */ ":%s 711 %s %s :Your KNOCK has been delivered.",
/* 712 ERR_TOOMANYKNOCK */ ":%s 712 %s %s :Too many KNOCKs (%s).",
/* 713 ERR_CHANOPEN */ ":%s 713 %s %s :Channel is open.",
/* 714 ERR_KNOCKONCHAN */ ":%s 714 %s %s :You are already on that channel.",
/* 715 */ NULL,
/* 716 RPL_TARGUMODEG */ ":%s 716 %s %s :is in +g mode (server side ignore)",
/* 717 RPL_TARGNOTIFY */ ":%s 717 %s %s :has been informed that you messaged them.",
/* 718 RPL_UMODEGMSG */ ":%s 718 %s %s :is messaging you, and you are umode +g.",
/* 719 */ NULL,
/* 720 */ NULL,
/* 721 */ NULL,
/* 722 */ NULL,
/* 723 ERR_NOPRIVS */ ":%s 723 %s %s :Insufficient oper privs.",
/* 724 RPL_TESTMASK */ ":%s 724 %s %s!%s@%s %u %u :Local/remote clients match.",
/* 725 RPL_TESTLINE */ ":%s 725 %s %c %ld %s :%s",
/* 726 RPL_NOTESTLINE */ ":%s 726 %s %s :No matches",
/* 727 */ NULL,
/* 728 */ NULL,
/* 729 */ NULL,
/* 730 */ NULL,
/* 731 */ NULL,
/* 732 */ NULL,
/* 733 */ NULL,
/* 734 */ NULL,
/* 735 */ NULL,
/* 736 */ NULL,
/* 737 */ NULL,
/* 738 */ NULL,
/* 739 */ NULL,
/* 740 */ NULL,
/* 741 */ NULL,
/* 742 */ NULL,
/* 743 */ NULL,
/* 744 */ NULL,
/* 745 */ NULL,
/* 746 */ NULL,
/* 747 */ NULL,
/* 748 */ NULL,
/* 749 */ NULL,
/* 750 */ NULL,
/* 751 */ NULL,
/* 752 */ NULL,
/* 753 */ NULL,
/* 754 */ NULL,
/* 755 */ NULL,
/* 756 */ NULL,
/* 757 */ NULL,
/* 758 */ NULL,
/* 759 */ NULL,
/* 760 */ NULL,
/* 761 */ NULL,
/* 762 */ NULL,
/* 763 */ NULL,
/* 764 */ NULL,
/* 765 */ NULL,
/* 766 */ NULL,
/* 767 */ NULL,
/* 768 */ NULL,
/* 769 */ NULL,
/* 770 */ NULL,
/* 771 */ NULL,
/* 772 */ NULL,
/* 773 */ NULL,
/* 774 */ NULL,
/* 775 */ NULL,
/* 776 */ NULL,
/* 777 */ NULL,
/* 778 */ NULL,
/* 779 */ NULL,
/* 780 */ NULL,
/* 781 */ NULL,
/* 782 */ NULL,
/* 783 */ NULL,
/* 784 */ NULL,
/* 785 */ NULL,
/* 786 */ NULL,
/* 787 */ NULL,
/* 788 */ NULL,
/* 789 */ NULL,
/* 790 */ NULL,
/* 791 */ NULL,
/* 792 */ NULL,
/* 793 */ NULL,
/* 794 */ NULL,
/* 795 */ NULL,
/* 796 */ NULL,
/* 797 */ NULL,
/* 798 */ NULL,
/* 799 */ NULL,
/* 800 */ NULL,
/* 801 */ NULL,
/* 802 */ NULL,
/* 803 */ NULL,
/* 804 */ NULL,
/* 805 */ NULL,
/* 806 */ NULL,
/* 807 */ NULL,
/* 808 */ NULL,
/* 809 */ NULL,
/* 810 */ NULL,
/* 811 */ NULL,
/* 812 */ NULL,
/* 813 */ NULL,
/* 814 */ NULL,
/* 815 */ NULL,
/* 816 */ NULL,
/* 817 */ NULL,
/* 818 */ NULL,
/* 819 */ NULL,
/* 820 */ NULL,
/* 821 */ NULL,
/* 822 */ NULL,
/* 823 */ NULL,
/* 824 */ NULL,
/* 825 */ NULL,
/* 826 */ NULL,
/* 827 */ NULL,
/* 828 */ NULL,
/* 829 */ NULL,
/* 830 */ NULL,
/* 831 */ NULL,
/* 832 */ NULL,
/* 833 */ NULL,
/* 834 */ NULL,
/* 835 */ NULL,
/* 836 */ NULL,
/* 837 */ NULL,
/* 838 */ NULL,
/* 839 */ NULL,
/* 840 */ NULL,
/* 841 */ NULL,
/* 842 */ NULL,
/* 843 */ NULL,
/* 844 */ NULL,
/* 845 */ NULL,
/* 846 */ NULL,
/* 847 */ NULL,
/* 848 */ NULL,
/* 849 */ NULL,
/* 850 */ NULL,
/* 851 */ NULL,
/* 852 */ NULL,
/* 853 */ NULL,
/* 854 */ NULL,
/* 855 */ NULL,
/* 856 */ NULL,
/* 857 */ NULL,
/* 858 */ NULL,
/* 859 */ NULL,
/* 860 */ NULL,
/* 861 */ NULL,
/* 862 */ NULL,
/* 863 */ NULL,
/* 864 */ NULL,
/* 865 */ NULL,
/* 866 */ NULL,
/* 867 */ NULL,
/* 868 */ NULL,
/* 869 */ NULL,
/* 870 */ NULL,
/* 871 */ NULL,
/* 872 */ NULL,
/* 873 */ NULL,
/* 874 */ NULL,
/* 875 */ NULL,
/* 876 */ NULL,
/* 877 */ NULL,
/* 878 */ NULL,
/* 879 */ NULL,
/* 880 */ NULL,
/* 881 */ NULL,
/* 882 */ NULL,
/* 883 */ NULL,
/* 884 */ NULL,
/* 885 */ NULL,
/* 886 */ NULL,
/* 887 */ NULL,
/* 888 */ NULL,
/* 889 */ NULL,
/* 890 */ NULL,
/* 891 */ NULL,
/* 892 */ NULL,
/* 893 */ NULL,
/* 894 */ NULL,
/* 895 */ NULL,
/* 896 */ NULL,
/* 897 */ NULL,
/* 898 */ NULL,
/* 899 */ NULL,
/* 900 */ NULL,
/* 901 */ NULL,
/* 902 */ NULL,
/* 903 */ NULL,
/* 904 */ NULL,
/* 905 */ NULL,
/* 906 */ NULL,
/* 907 */ NULL,
/* 908 */ NULL,
/* 909 */ NULL,
/* 910 */ NULL,
/* 911 */ NULL,
/* 912 */ NULL,
/* 913 */ NULL,
/* 914 */ NULL,
/* 915 */ NULL,
/* 916 */ NULL,
/* 917 */ NULL,
/* 918 */ NULL,
/* 919 */ NULL,
/* 920 */ NULL,
/* 921 */ NULL,
/* 922 */ NULL,
/* 923 */ NULL,
/* 924 */ NULL,
/* 925 */ NULL,
/* 926 */ NULL,
/* 927 */ NULL,
/* 928 */ NULL,
/* 929 */ NULL,
/* 930 */ NULL,
/* 931 */ NULL,
/* 932 */ NULL,
/* 933 */ NULL,
/* 934 */ NULL,
/* 935 */ NULL,
/* 936 */ NULL,
/* 937 */ NULL,
/* 938 */ NULL,
/* 939 */ NULL,
/* 940 */ NULL,
/* 941 */ NULL,
/* 942 */ NULL,
/* 943 */ NULL,
/* 944 */ NULL,
/* 945 */ NULL,
/* 946 */ NULL,
/* 947 */ NULL,
/* 948 */ NULL,
/* 949 */ NULL,
/* 950 */ NULL,
/* 951 */ NULL,
/* 952 */ NULL,
/* 953 */ NULL,
/* 954 */ NULL,
/* 955 */ NULL,
/* 956 */ NULL,
/* 957 */ NULL,
/* 958 */ NULL,
/* 959 */ NULL,
/* 960 */ NULL,
/* 961 */ NULL,
/* 962 */ NULL,
/* 963 */ NULL,
/* 964 */ NULL,
/* 965 */ NULL,
/* 966 */ NULL,
/* 967 */ NULL,
/* 968 */ NULL,
/* 969 */ NULL,
/* 970 */ NULL,
/* 971 */ NULL,
/* 972 */ NULL,
/* 973 */ NULL,
/* 974 */ NULL,
/* 975 */ NULL,
/* 976 */ NULL,
/* 977 */ NULL,
/* 978 */ NULL,
/* 979 */ NULL,
/* 980 */ NULL,
/* 981 */ NULL,
/* 982 */ NULL,
/* 983 */ NULL,
/* 984 */ NULL,
/* 985 */ NULL,
/* 986 */ NULL,
/* 987 */ NULL,
/* 988 */ NULL,
/* 989 */ NULL,
/* 990 */ NULL,
/* 991 */ NULL,
/* 992 */ NULL,
/* 993 */ NULL,
/* 994 */ NULL,
/* 995 */ NULL,
/* 996 */ NULL,
/* 997 */ NULL,
/* 998 */ NULL,
/* 999 ERR_LAST_ERR_MSG */ ":%s 999 %s :Last Error Message"
};

/*
 * form_str
 *
 * inputs       - numeric
 * output       - corresponding string
 * side effects - NONE
 */
const char *
form_str(unsigned int numeric)
{
  assert(numeric < ERR_LAST_ERR_MSG);

  if (numeric > ERR_LAST_ERR_MSG)
    numeric = ERR_LAST_ERR_MSG;

  assert(replies[numeric]);

  return replies[numeric];
}
