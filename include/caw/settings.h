#pragma once

typedef struct settings_t settings_t;

settings_t *settings_open();

void settings_close(settings_t *settings);

bool settings_ready(const settings_t *settings);

bool settings_flush(const settings_t *settings);

const char *settings_string(settings_t *settings, const char *key, const char *fallback);
bool settings_set_string(settings_t *settings, const char *key, const char *value);
