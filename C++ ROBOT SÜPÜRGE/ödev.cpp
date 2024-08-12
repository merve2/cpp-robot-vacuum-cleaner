#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
const int MAX_GENISLIK = 100;
const int MAX_YUKSEKLIK = 50;

class Robot {
public:
    static int pil_ömrü;
    static void setPilÖmrü(int yeniDeger) {
        pil_ömrü = yeniDeger;
    }
    // Soyut move fonksiyonu
    virtual void move() = 0;
    // Parametreli constructor
    Robot() {}
};

class Room {
private:
    int roomMatrix[MAX_YUKSEKLIK][MAX_GENISLIK];
    int engel[MAX_YUKSEKLIK][MAX_GENISLIK];
    bool temizMi[MAX_YUKSEKLIK][MAX_GENISLIK];

public:
    int x, y;
    int hiz_seviyesi;
    Room() : x(MAX_GENISLIK), y(MAX_YUKSEKLIK), hiz_seviyesi(1) {
        // Oda matrisini oluştur
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < x; ++j) {
                roomMatrix[i][j] = ' ';
                engel[i][j] = false;
                temizMi[i][j] = false;
            }
        }
    }

    void printRoom() const {
        for (int i = 0; i < y; ++i) {
            for (int j = 0; j < x; ++j) {
                cout << roomMatrix[i][j] << ' ';
            }
            cout << endl;
        }
    }

    void cleanRoom(int startX, int startY, int endX, int endY, int hizSeviyesi) {
        float dususOrani;
        if (hizSeviyesi == 1) {
            dususOrani = 0.2;
        }
        else if (hizSeviyesi == 2) {
            dususOrani = 0.3;
        }
        else {
            cout << "Hatali hiz seviyesi!" << endl;
            return;
        }

        for (int i = startY; i <= endY; ++i) {
            for (int j = startX; j <= endX; ++j) {
                // Eğer engel yoksa ve temiz değilse temizle
                if (!engel[i][j] && !temizMi[i][j]) {
                    cout << "Temizlik işlemi konumunda (" << i << ", " << j << ")" << endl;
                    temizMi[i][j] = true;
                }
            }
        }

        Robot::setPilÖmrü(Robot::pil_ömrü - dususOrani);
        cout << "Temizlik islemi tamamlandi. Kalan pil seviyesi: " << Robot::pil_ömrü << endl;
    }

    // Engeli belirleme fonksiyonu
    void setObstacle(int x, int y) {
        engel[y][x] = true;
    }
};

class RobotSweeper : public Robot {
private:
    int moppingWater;
    int mesafe;

public:
    Room* currentRoom;
    int currentX;
    int currentY;
    int hedefX, hedefY;
    bool temizlik;
    int hizSeviyesi;
    float pilSeviyesi;

    RobotSweeper(float baslangicPilSeviyesi) : pilSeviyesi(baslangicPilSeviyesi), currentX(0), currentY(0), currentRoom(nullptr) {}

    // Move fonksiyonunu yeniden tanımla
    void move() override {
        cout << "Hedef koordinatlari girin (x1 y1 x2 y2): ";
        int startX, startY, endX, endY;
        cin >> startX >> startY >> endX >> endY;

        cout << "Hiz seviyesini secin (1 veya 2): ";
        cin >> hizSeviyesi;

        cout << "Temizlik turunu secin (1:silme, 2:supurme): ";
        int temizlikTuru;
        cin >> temizlikTuru;

        if (currentRoom) {
            mesafe = abs(currentX - startX) + abs(currentY - startY);
            currentRoom->cleanRoom(startX, startY, endX, endY, hizSeviyesi);

            if (temizlikTuru == 1) {
                // Silme işlemi ile ilgili kodlar buraya eklenebilir.
                cout << "Silme islemi yapiliyor." << endl;
            }
            else if (temizlikTuru == 2) {
                // Süpürme işlemi ile ilgili kodlar buraya eklenebilir.
                cout << "Süpürme islemi yapiliyor." << endl;
            }
            else {
                cout << "Geçersiz temizlik turu!" << endl;
            }
        }

        // Geri dönüş işlemi, şarj istasyonuna dönülmesi gibi durumlar burada eklenebilir.

        // Pil seviyesini güncelle
        cout << "Robot hareketi tamamlandi. Kalan pil seviyesi: " << pilSeviyesi << endl;
    }
};

int Robot::pil_ömrü = 100; // Statik üye değişkenin tanımı

int main() {
    // RobotSweeper objesini oluştur
    RobotSweeper robot(100.0);

    // Oda nesnesini oluştur ve engel belirle
    Room oda;
    oda.setObstacle(1, 1);
    oda.setObstacle(2, 2);
    oda.setObstacle(3, 3);

    // Robotun bulunduğu odayı ayarla
    robot.currentRoom = &oda;

    // Robot hareketi gerçekleştir
    robot.move();

    return 0;
}
