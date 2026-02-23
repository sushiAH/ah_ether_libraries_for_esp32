#include <esp32_w5500.h>

struct __attribute__((packed)) PacketData {
    uint32_t time_ms;
    uint32_t motor_id;
};

void init_w5500(int esp32_id, EthernetUDP *udp)
{
    const int W5500_CS_PIN = 5;

    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, esp32_id};
    IPAddress ip(192, 168, 10, esp32_id); // esp32_ip
    IPAddress subnet(255, 255, 255, 0);

    Ethernet.init(W5500_CS_PIN);
    Ethernet.begin(mac, ip, ip, ip, subnet);

    udp->begin(8888); // 8888 is localport
}

void receive_packet()
{
    if (packet_size) {
        if (packet_size == sizeof(SensorData)) {
            SensorData packet;
            udp.read((uint8_t *)&packet, sizeof(SensorData));
            Serial.println(packet.motor_id);
        } else {
            char flush_buf[256];
            udp.read(flush_buf, 256);
        }
    }
}

void send_packet();
