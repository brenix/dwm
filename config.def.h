/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const int startwithgaps      = 1;        /* 1 means gaps are used by default */
static const unsigned int gappx     = 5;        /* default gap between windows in pixels */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "terminus:size=10" };
static const char dmenufont[]       = "terminus:size=10";
static const char col_gray1[]       = "#101010";
static const char col_gray2[]       = "#454545";
static const char col_gray3[]       = "#999999";
static const char col_gray4[]       = "#b9b9b9";
static const char col_gray5[]       = "#252525";
static const char *colors[][3]      = {
  /*               fg         bg         border   */
  [SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
  [SchemeSel]  = { col_gray4, col_gray5, col_gray2 },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4" };

static const Rule rules[] = {
  /* xprop(1):
   *  WM_CLASS(STRING) = instance, class
   *  WM_NAME(STRING) = title
   */
  /* class         instance    title       tags mask     isfloating   monitor */
  { "Alacritty",   "floating", NULL,       0,            1,           -1 },
  { "Authy",       NULL,       NULL,       0,            1,           -1 },
  { "Firefox",     NULL,       NULL,       1 << 3,       0,           -1 },
  { "Gimp",        NULL,       NULL,       0,            1,           -1 },
  { "Pavucontrol", NULL,       NULL,       0,            1,           -1 },
  { "Slack",       NULL,       NULL,       1 << 2,       0,           -1 },
  { "Spotify",     NULL,       NULL,       1 << 4,       0,           -1 },
  { "zoom",        NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
static const int mainmon = 0; /* xsetroot will only change the bar on this monitor */

static const Layout layouts[] = {
  /* symbol     arrange function */
  { "[]=",      tile },    /* first entry is default */
  { "><>",      NULL },    /* no layout function means floating behavior */
  { "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
  { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
  { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
  { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]        = { "dmenu_run", "-c", "-l", "20", "-i", NULL };
static const char *termcmd[]         = { "alacritty", NULL };
static const char *termfloatcmd[]    = { "alacritty", "--class", "Alacritty,floating", NULL };
static const char *browsercmd[]      = { "firefox", NULL };
static const char *musiccmd[]        = { "spotify", NULL };
static const char *notescmd[]        = { "obsidian", NULL };
static const char *slackcmd[]        = { "slack", NULL };
static const char *slackchannelcmd[] = { "xdg-open", "'slack://channel?team=T024JFTN4&id=GHMTDF91B'", NULL };
static const char *volumecmd[]       = { "pavucontrol", NULL };
static const char *voldown[]         = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "2%-", NULL };
static const char *volup[]           = { "wpctl", "set-volume", "@DEFAULT_AUDIO_SINK@", "2%+", NULL };
static const char *volmute[]         = { "wpctl", "set-mute", "@DEFAULT_AUDIO_SOURCE@", "toggle", NULL };
static const char *playnext[]        = { "playerctl", "next", NULL };
static const char *playprev[]        = { "playerctl", "previous", NULL };
static const char *playpause[]       = { "playerctl", "play-pause", NULL };
static const char *playstop[]        = { "playerctl", "stop", NULL };

#include <X11/XF86keysym.h>
static const Key keys[] = {
  /* modifier                     key        function        argument */
  { MODKEY,                       XK_space,  spawn,          {.v = dmenucmd } },
  { MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termfloatcmd } },
  { MODKEY,                       XK_b,      togglebar,      {0} },
  { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
  { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
  { MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
  { MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
  { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
  { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
  { MODKEY,                       XK_Tab,    view,           {0} },
  { MODKEY,                       XK_w,      killclient,     {0} },
  { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
  { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[1]} },
  { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
  { MODKEY,                       XK_f,      togglefloating, {0} },
  { MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },
  { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
  { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
  { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
  { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
  { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
  { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
  { MODKEY,                       XK_minus,  setgaps,        {.i = -5 } },
  { MODKEY,                       XK_equal,  setgaps,        {.i = +5 } },
  { MODKEY|ShiftMask,             XK_minus,  setgaps,        {.i = GAP_RESET } },
  { MODKEY|ShiftMask,             XK_equal,  setgaps,        {.i = GAP_TOGGLE} },
  TAGKEYS(                        XK_1,                      0)
  TAGKEYS(                        XK_2,                      1)
  TAGKEYS(                        XK_3,                      2)
  TAGKEYS(                        XK_4,                      3)
  { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
  { MODKEY,                       XK_d,      spawn,          {.v = browsercmd } },
  { MODKEY,                       XK_s,      spawn,          {.v = musiccmd } },
  { MODKEY|ShiftMask,             XK_s,      spawn,          {.v = slackcmd } },
  { MODKEY,                       XK_e,      spawn,          {.v = slackchannelcmd } },
  { MODKEY,                       XK_o,      spawn,          {.v = notescmd } },
  { MODKEY,                       XK_v,      spawn,          {.v = volumecmd } },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn, {.v = volup } },
  { 0,                            XF86XK_AudioLowerVolume,   spawn, {.v = voldown } },
  { 0,                            XF86XK_AudioMute,          spawn, {.v = volmute } },
  { 0,                            XF86XK_AudioNext,          spawn, {.v = playnext } },
  { 0,                            XF86XK_AudioPrev,          spawn, {.v = playprev } },
  { 0,                            XF86XK_AudioPlay,          spawn, {.v = playpause } },
  { 0,                            XF86XK_AudioStop,          spawn, {.v = playstop } },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
  /* click                event mask      button          function        argument */
  { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
  { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
  { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
  { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
  { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
  { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
  { ClkTagBar,            0,              Button1,        view,           {0} },
  { ClkTagBar,            0,              Button3,        toggleview,     {0} },
  { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
  { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
