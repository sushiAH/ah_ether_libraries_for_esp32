/*esp32_w5500ライブラリ
 * esp32のipは、192.168.10.esp32_idとする
 * 待ち受けるポートは8888とする*/

#include <esp32_w5500.h>

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

bool receive_packet(EthernetUDP *udp, RxPacket *packet)
{
    int packet_size = udp->parsePacket();

    if (packet_size == 0) {
        return false;
    }

    if (packet_size != sizeof(RxPacket)) {
        char flush_buf[256];
        udp->read(flush_buf, 256);
        return false;
    }

    udp->read((uint8_t *)&packet, sizeof(RxPacket));
}

void send_packet(TxPacket *packet, EthernetUDP *udp, int pc_ip)
{
    pc_port = 12345;
    udp->beginPacket(pc_ip, pc_port);
    udp->write((const uint8_t *)packet, sizeof(TxPacket));
    udp->endPacket();
}
