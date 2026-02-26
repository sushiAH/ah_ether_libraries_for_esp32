#ifndef ESP32_W5500_H
#define ESP32_W5500_H

#include <Arduino.h>
#include <EthernetUdp.h>
#include <SPI.h>
#include <WiFi.h>
#include <ah_control_table.h>
#include <ah_pid_esp.h>

struct __attribute__((packed)) TxPacket {
    uint32_t imu_data;
};

struct __attribute__((packed)) RxPacket {
    uint32_t motor_id;
    uint32_t table_addr;
    uint32_t target;
};

void init_w5500(int esp32_id, EthernetUDP *udp);

bool receive_packet(EthernetUDP *udp, RxPacket *packet);

void send_packet(TxPacket *packet, EthernetUDP *udp, const char *pc_ip);

#endif
