#define COLOR(hex)    { ((hex >> 24) & 0xFF) / 255.0f, \
                        ((hex >> 16) & 0xFF) / 255.0f, \
                        ((hex >> 8) & 0xFF) / 255.0f, \
                        (hex & 0xFF) / 255.0f }

static const int sloppyfocus               = 1;  /* focus follows mouse */
static const int bypass_surface_visibility = 0;
static const unsigned int borderpx         = 1;  /* border pixel of windows */
//static const float rootcolor[]             = COLOR(0x222222ff);
//static const float bordercolor[]           = COLOR(0x2c2e2eff);
//static const float focuscolor[]            = COLOR(0x576357ff);
//static const float urgentcolor[]           = COLOR(0xff5050ff);
static const int user_bh		           = 18;
static const int showbar                   = 1; /* 0 means no bar */
static const int topbar                    = 1; /* 0 means bottom bar */
static const char *fonts[]                 = {"DejaVu Sans Mono:size=10"};
static const float rootcolor[]             = COLOR(0x000000ff);
static const float fullscreen_bg[]         = COLOR(0x1a1a1aff);

static uint32_t colors[][3] = {
	/*               fg          bg          border    */
	[SchemeNorm] = { 0xddddddff, 0x1c1e1eff, 0x2c2e2eff },
	[SchemeSel]  = { 0xddddddff, 0x206141ff, 0x576357ff },
	[SchemeUrg]  = { 0xffffffff, 0xff5050ff, 0xff5050ff },
};

static char *tags[] = { "1", "2", "3", "4" };

static const char *const autostart[] = {
	"pipewire", NULL,
	"pipewire-pulse", NULL,
	"wireplumber", NULL,
	"swaybg", "-mfill", "-i/home/joe/wallpapers/void.png", NULL,
    NULL
};

static int log_level = WLR_ERROR;

static const Rule rules[] = {
	/* app_id              title       tags mask     isfloating   monitor */
	{ "floating",          NULL,       0,            1,           -1 },
	{ "galculator",        NULL,       0,            1,           -1 },
};

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

static const MonitorRule monrules[] = {
	/* name       mfact  nmaster scale layout       rotate/reflect                x    y */
	{ NULL,       0.5f,  1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL,   -1,  -1 },
};

static const struct xkb_rule_names xkb_rules = {
	.layout = "us,us(intl)",
	.options = "grp:shifts_toggle",
};

static const int repeat_rate = 30;
static const int repeat_delay = 200;

static const char *cursor_theme = "Adwaita-Classic";
static const char *cursor_size = "16";

static const int tap_to_click = 1;
static const int tap_and_drag = 1;
static const int drag_lock = 0;
static const int natural_scrolling = 1;
static const int disable_while_typing = 0;
static const int left_handed = 0;
static const int middle_button_emulation = 1;
static const double touchpad_scroll_factor = 0.2;
static const unsigned int swipe_min_threshold = 0;

static const enum libinput_config_scroll_method scroll_method = LIBINPUT_CONFIG_SCROLL_2FG;
static const enum libinput_config_click_method click_method = LIBINPUT_CONFIG_CLICK_METHOD_BUTTON_AREAS;
static const uint32_t send_events_mode = LIBINPUT_CONFIG_SEND_EVENTS_ENABLED;
static const enum libinput_config_accel_profile accel_profile = LIBINPUT_CONFIG_ACCEL_PROFILE_ADAPTIVE;
static const double accel_speed = 0.0;
static const enum libinput_config_tap_button_map button_map = LIBINPUT_CONFIG_TAP_MAP_LRM;

#define SUPER WLR_MODIFIER_LOGO
#define ALT WLR_MODIFIER_ALT
#define CTRL WLR_MODIFIER_CTRL
#define SHIFT WLR_MODIFIER_SHIFT

#define TAGKEYS(KEY,SKEY,TAG) \
	{ SUPER,                       KEY,            view,            {.ui = 1 << TAG} }, \
	{ SUPER|CTRL,                  KEY,            toggleview,      {.ui = 1 << TAG} }, \
	{ SUPER|SHIFT,                 SKEY,           tag,             {.ui = 1 << TAG} }, \
	{ SUPER|CTRL|SHIFT,            SKEY,           toggletag,       {.ui = 1 << TAG} }

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/bash", "-c", cmd, NULL } }

static const Key keys[] = {
	/* modifier                  key                   function          argument */
	{ ALT,           XKB_KEY_space,                    spawn,            SHCMD("menu-desktop") },
	{ SUPER,         XKB_KEY_Return,                   spawn,            SHCMD("foot") },
	{ SUPER|SHIFT,   XKB_KEY_Return,                   spawn,            SHCMD("foot -a floating") },
	{ SUPER,         XKB_KEY_e,                        spawn,            SHCMD("foot nnn") },
	{ SUPER,         XKB_KEY_w,                        spawn,            SHCMD("firefox") },
	{ 0,             XKB_KEY_XF86TouchpadToggle,       spawn,            SHCMD("foot -a floating bluetoothctl") },
	{ 0,             XKB_KEY_XF86WebCam,               spawn,            SHCMD("foot -a floating iwctl") },
	{ 0,             XKB_KEY_XF86Calculator,           spawn,            SHCMD("galculator") },
	{ 0,             XKB_KEY_XF86Launch1,              spawn,            SHCMD("toggle-theme") },
	{ SUPER,         XKB_KEY_p,                        spawn,            SHCMD("toggle-display") },
	{ 0,             XKB_KEY_XF86MonBrightnessUp,      spawn,            SHCMD("brightnessctl set +5%") },
	{ 0,             XKB_KEY_XF86MonBrightnessDown,    spawn,            SHCMD("brightnessctl set 5%-") },
	{ 0,             XKB_KEY_XF86AudioMute,            spawn,            SHCMD("wpctl set-mute @DEFAULT_SINK@ toggle") },
	{ 0,             XKB_KEY_XF86AudioRaiseVolume,     spawn,            SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%+") },
	{ 0,             XKB_KEY_XF86AudioLowerVolume,     spawn,            SHCMD("wpctl set-volume @DEFAULT_SINK@ 5%-") },
	{ CTRL,          XKB_KEY_space,                    spawn,            SHCMD("playerctl play-pause") },
	{ 0,             XKB_KEY_Print,                    spawn,            SHCMD("grim >(wl-copy)") },
	{ SUPER|SHIFT,   XKB_KEY_S,                        spawn,            SHCMD("grim -g \"$(slurp)\" >(wl-copy)") },
	{ SUPER,         XKB_KEY_s,                        spawn,            SHCMD("toggle-sleep-inhibition") },
	{ 0,             XKB_KEY_XF86PowerOff,             spawn,            SHCMD("doas zzz") },
	{ SUPER,         XKB_KEY_h,                        spawn,            SHCMD("doas ZZZ") },
	{ SUPER,         XKB_KEY_b,                        togglebar,        {0} },
	{ SUPER,         XKB_KEY_l,                        focusstack,       {.i = +1} },
	{ SUPER,         XKB_KEY_k,                        focusstack,       {.i = -1} },
	{ SUPER,         XKB_KEY_i,                        incnmaster,       {.i = +1} },
	{ SUPER,         XKB_KEY_u,                        incnmaster,       {.i = -1} },
	{ SUPER,         XKB_KEY_j,                        setmfact,         {.f = -0.05f} },
	{ SUPER,         XKB_KEY_semicolon,                setmfact,         {.f = +0.05f} },
	{ SUPER,         XKB_KEY_o,                        zoom,             {0} },
	{ SUPER,         XKB_KEY_Tab,                      view,             {0} },
	{ SUPER,         XKB_KEY_q,                        killclient,       {0} },
	{ SUPER,         XKB_KEY_x,                        setlayout,        {.v = &layouts[0]} },
	{ SUPER,         XKB_KEY_z,                        setlayout,        {.v = &layouts[1]} },
	{ SUPER,         XKB_KEY_a,                        setlayout,        {.v = &layouts[2]} },
	{ SUPER,         XKB_KEY_space,                    togglefloating,   {0} },
	{ SUPER,         XKB_KEY_f,                        togglefullscreen, {0} },
	{ SUPER,         XKB_KEY_0,                        view,             {.ui = ~0} },
	{ SUPER|SHIFT,   XKB_KEY_parenright,               tag,              {.ui = ~0} },
	{ SUPER,         XKB_KEY_bracketleft,              focusmon,         {.i = WLR_DIRECTION_LEFT} },
	{ SUPER,         XKB_KEY_bracketright,             focusmon,         {.i = WLR_DIRECTION_RIGHT} },
	{ SUPER|SHIFT,   XKB_KEY_braceleft,                tagmon,           {.i = WLR_DIRECTION_LEFT} },
	{ SUPER|SHIFT,   XKB_KEY_braceright,               tagmon,           {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(         XKB_KEY_m,                        XKB_KEY_M,        0),
	TAGKEYS(         XKB_KEY_comma,                    XKB_KEY_less,     1),
	TAGKEYS(         XKB_KEY_period,                   XKB_KEY_greater,  2),
	TAGKEYS(         XKB_KEY_slash,                    XKB_KEY_question, 3),
	{ SUPER|SHIFT,   XKB_KEY_Q,                        quit,             {0} },
	{ CTRL|ALT,      XKB_KEY_Terminate_Server,         quit,             {0} },

#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4),
};

static const Button buttons[] = {
//	{ SUPER,         BTN_LEFT,                         moveresize,       {.ui = CurMove} },
//	{ SUPER,         BTN_MIDDLE,                       togglefloating,   {0} },
//	{ SUPER,         BTN_RIGHT,                        moveresize,       {.ui = CurResize} },
	{ ClkClient,   SUPER,  BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ ClkClient,   SUPER,  BTN_MIDDLE, togglefloating, {0} },
	{ ClkClient,   SUPER,  BTN_RIGHT,  moveresize,     {.ui = CurResize} },
	{ ClkTagBar,   0,      BTN_LEFT,   view,           {0} },
	{ ClkTagBar,   0,      BTN_RIGHT,  toggleview,     {0} },
	{ ClkTagBar,   SUPER,  BTN_LEFT,   tag,            {0} },
	{ ClkTagBar,   SUPER,  BTN_RIGHT,  toggletag,      {0} },
};

static const Gesture gestures[] = {
	{ 0,             SWIPE_DOWN,           3,          togglekeyboard,   {0} },
};
