// AGPLv3 License
// Copyright (c) 2019 Danny Angelo Carminati Grein

/* clang-format off */
#ifndef CFG_FIELD
#error "x-macros, please define a CFG_FIELD macro on how to interpret the values"
#define CFG_FIELD(section, name, default, type)
#endif

CFG_FIELD(global, auto_close, "yes", bool)
// default: yes
// auto close after launching the client

CFG_FIELD(global, check_updates, "yes", bool)

CFG_FIELD(global, auto_update, "yes", bool)

CFG_FIELD(global, beta_channel, "no", bool)

CFG_FIELD(account, profile, {}, astr_t)

CFG_FIELD(account, login, {}, astr_t)

CFG_FIELD(account, password, {}, astr_t)

CFG_FIELD(account, auto_login, "no", bool)

CFG_FIELD(account, save_password, "no", bool)

CFG_FIELD(account, data_path, {}, astr_t)

CFG_FIELD(account, fast_login, {}, astr_t) // character name

CFG_FIELD(account, extra_cli, {}, astr_t)

// --- BEGIN fields from cfg_shard.h
CFG_FIELD(account, loginserver, {}, astr_t)
// required
// same as crossuop.cfg, classic loginserver for login.cfg
// format:
//   <ip>,<port>

CFG_FIELD(account, clientversion, {}, astr_t)
// required
// same as in crossuo.cfg, specify the client version to emulate with crossuo

CFG_FIELD(account, protocolversion, {}, astr_t)
// required
// same as in crossuo.cfg, specify the network protocol version to force

CFG_FIELD(account, clienttype, {}, astr_t)
// optional
// same as crossuo.cfg, if empty will autodetect based on the client version

CFG_FIELD(account, crypt, "no", bool)
// otpional, default: no
// format:
//   <no|yes>
// if 'yes', uo protocol cryptography will be used

// --- END fields from cfg_shard.h


#undef CFG_FIELD
