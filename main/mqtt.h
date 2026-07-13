/*
 * This file is part of the WiCAN project.
 *
 * Copyright (C) 2022  Meatpi Electronics.
 * Written by Ali Slim <ali@meatpi.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MQTT_h
#define MQTT_h

#include <stdbool.h>
#include <stdint.h>
#include "driver/twai.h"
#include "elm327.h"

#define MQTT_CAN        0x00
#define MQTT_RX         ELM327_CAN_RX
#define MQTT_TX         ELM327_CAN_TX

typedef struct
{
    uint8_t type;
    twai_message_t frame;
}mqtt_can_message_t;

// Snapshot of one broadcast CAN filter's latest computed value, for consumers
// (e.g. the AutoPID webhook payload) other than the MQTT publish this feature
// was originally built for.
typedef struct
{
    char name[16];
    char unit[16];
    char class_name[24];
    float value;
    bool has_value;
} mqtt_canflt_entry_t;

void mqtt_init(char* id, uint8_t connected_led, QueueHandle_t *xtx_queue);
int mqtt_connected(void);
void mqtt_publish(char *topic, char *data, int len, int qos, int retain);

// Broadcast CAN filter ("CAN to JSON interpreter") accessors. These work
// independent of whether MQTT itself is enabled/connected.
bool mqtt_canflt_configured(void);
bool mqtt_canflt_is_active(void);
uint32_t mqtt_canflt_get_count(void);
bool mqtt_canflt_get_entry(uint32_t index, mqtt_canflt_entry_t *out);
#endif
