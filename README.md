# Sisop-5-2025-IT-Template

## Kelompok

Nama | NRP
--- | ---
Nisrina Bilqis | 5027241054
Dina Rahmadani | 5027241065
Hanif Mawla Faizi | 5027241064

## Daftar Isi

- [Kelompok](#kelompok)
- [Daftar Isi](#daftar-isi)
- [Soal](#soal)
- [Petunjuk Soal](#petunjuk-soal)
  - [Source](#source)
  - [Headers](#headers)
  - [Makefile](#makefile)
  - [Video Demonstrasi](#video-demonstrasi)
- [Laporan](#laporan)

## Soal

Pada suatu hari, anda merasa sangat lelah dari segala macam praktikum yang sudah ada, sehingga anda berencana untuk tidur yang nyenyak di sebuah jam 3:34AM yang cerah. Tetapi, anda terbangun di dalam dunia berbeda yang bernama "Eorzea". Ada sesuatu yang mengganggu pikiran anda sehingga anda diharuskan membuat sebuah operating system bernama "EorzeOS" untuk mendampingi diri anda dalam dunia ini.

1. Sebagai seorang main character dari dunia ini, ternyata anda memiliki kekuatan yang bernama "The Echo", kekuatan ini memungkinkan anda untuk berbicara pada Operating System ini (mungkin sebenarnya bukan ini kekuatannya, tetapi ini cukup kuat juga), dengan tujuan agar semua hal yang anda katakan, bila bukan merupakan sebuah command yang valid, akan mengulang hal yang anda katakan.

   Ilustrasi:
   ```
   user> Hello!
   Hello!
   user> I have the Echo
   I have the Echo
   ```

    Jawab :

     1.Fungsi `readString` :
    
    Fungsi ini digunakan untuk membaca input dari pengguna melalui keyboard.
      ```c
      void readString(char *buf)
      {
        int i = 0;
        char c = 0;
        while (1) {
          c = interrupt(0x16, 0x0000, 0, 0, 0); // Layanan BIOS: Keyboard input
          if (c == '\r') { // Enter key
            buf[i] = '\0'; // Akhirkan string saat Enter ditekan
            printString("\r\n"); // Pindah baris
            break;
          } else if (c == '\b') { // Backspace
            if (i > 0) {
              i--; // Hapus karakter sebelumnya
              printString("\b \b"); // Tampilkan backspace
            }
          } else {
            buf[i++] = c;
            printString(str); // Menampilkan karakter yang dimasukkan
          }
        }
      }
      ```
      Penjelasan:
      - Fungsi ini membaca satu karakter per satu dari input keyboard.
      - Input akan disimpan dalam buffer dan ditampilkan pada layar.
      - Setelah Enter ditekan, input diselesaikan dengan karakter null (`'\0'`), menandakan akhir dari input.
    
    
     2.Fungsi `printString` :
    
      Fungsi ini digunakan untuk menampilkan string yang diberikan.
      ```c
      void printString(char *str)
      {
        while (*str != '\0') {
          interrupt(0x10, 0x0E00 + *str, 0, 0, 0); // Menampilkan karakter dengan BIOS
          str++;
        }
      }
      
      ```
      Penjelasan:
      - Fungsi ini menampilkan string ke layar menggunakan interrupt BIOS.
      - Setiap karakter dari string akan ditampilkan satu per satu.
    ---
    
3. gurt: yo

   Ilustrasi:
   ```
   user> yo
   gurt
   user> gurt
   yo
   ```

  Jawab :
  
  Fungsi `shell`:
  
  Fungsi ini menangani input dari pengguna dan memprosesnya.
  
  ```c
  void shell() {
    char buf[128], cmd[64], arg[2][64], username[64], company[64];
    strcpy(username, "user");
    strcpy(company, "");
  
    printString("Welcome to EorzeOS!\r\n");
    while (true) {
      info(username, company);
      readString(buf); // Membaca input
      parseCommand(buf, cmd, arg); // Memparse perintah dan argumen
  
      // Mengecek perintah "yo" dan "gurt"
      if (strcmp(cmd, "yo") == 0) {
        printString("gurt\r\n");
      } else if (strcmp(cmd, "gurt") == 0) {
        printString("yo\r\n");
      } else {
        printString(buf); // Mengulang input yang tidak dikenali
        printString("\r\n");
      }
    }
  }
  ```
  Penjelasan:
   - Di dalam fungsi shell, input pengguna dibaca dengan readString(buf).
   - Setelah itu, perintah yang dimasukkan akan diproses dengan fungsi parseCommand.
   - Program memeriksa apakah perintah yang dimasukkan adalah "yo" atau "gurt".
     - Jika perintah "yo" dimasukkan, sistem akan mencetak "gurt".
     - Jika perintah "gurt" dimasukkan, sistem akan mencetak "yo".
   - Jika perintah bukan "yo" atau "gurt", input yang tidak valid akan langsung ditampilkan kembali.
  
    ```c
    if (strcmp(cmd, "yo") == 0) {
      printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt") == 0) {
      printString("yo\r\n");
    }
    
    ```
  Contoh Output:
  - Pengguna mengetik "yo", maka sistem akan menampilkan "gurt".
  - Pengguna mengetik "gurt", maka sistem akan menampilkan "yo".
  
  ---

3. Seorang main character memerlukan sebuah nama yang semua orang bisa ingat dengan baik. Buatlah sebuah command yang memungkinkan pengguna untuk mengubah nama user pada shell yang digunakan:
   * `user <username>` = mengubah username menjadi `<username>`
   * `user` = mengubah username menjadi default `user`
   
   Ilustrasi:
   ```
   user> user Tia
   Username changed to Tia
   Tia> user
   Username changed to user
   user>
   ```

   Jawab :

   Fungsi `shell`:

   Fungsi ini menangani perintah user untuk mengubah username shell.
    ```c
    } else if(strcmp(cmd,"user")){
      if (arg[0][0] != '\0') {
        strcpy(username, arg[0]);
        printString("Username changed to: ");
        printString(username);
        printString("\r\n");
      } else {
        strcpy(username, "user");
        printString("Username changed to: user\r\n");
      }
    ```
    Penjelasan:
    -	Saat pengguna mengetik user <nama>, fungsi parseCommand akan menempatkan <nama> ke arg[0].
    -	Jika arg[0] tidak kosong, maka nama username akan diubah dengan strcpy(username, arg[0]);.
    -	Jika perintah hanya user tanpa argumen, maka nama username akan dikembalikan ke default, yaitu "user".
    -	Nama pengguna akan tampil di shell prompt melalui fungsi info.
    
    Contoh Output:
    -	Pengguna mengetik user Tia → prompt menjadi Tia>.
    -	Pengguna mengetik user → prompt kembali menjadi user>.

---

4. Tiga negara besar dari Eorzean Alliance butuh bantuan anda untuk ikut serta dalam "Grand Company" mereka sehingga anda bisa mengubah warna terminal ajaib anda sesuai warna utama dari company mereka:
   * `grandcompany maelstrom` = clear terminal, ubah semua teks berikutnya jadi merah
   * `grandcompany twinadder` = clear terminal, ubah semua teks berikutnya jadi kuning
   * `grandcompany immortalflames` = clear terminal, ubah semua teks berikutnya jadi biru
   * `grandcompany <selain atau kosong>` = tunjukkan error message
   * `clear` = clear terminal, ubah semua teks berikutnya kembali jadi awal (para Grand Company sedih kamu netral)

   Selain mengubah seluruh warna terminal, nama anda di dalam terminal akan diberikan tambahan nama judul Grand Company:
   * Maelstrom = `user@Storm`
   * Twin Adder = `user@Serpent`
   * Immortal Flames = `user@Flame`
   * `clear` = menghapus nama grand company

   Ilustrasi:
   ```
   gurt> grandcompany maelstrom
   -- terminal clear menjadi warna merah --
   gurt@Storm> clear
   -- terminal clear menjadi warna putih --
   ```

   Jawab :

     1.Fungsi `shell`:

   Fungsi ini menangani perintah grandcompany untuk bergabung dengan Grand Company tertentu dan mengubah prompt shell.
    ```c
    } else if(strcmp(cmd,"grandcompany")){
      if(strcmp(arg[0],"maelstrom")){
        strcpy(company, "@Storm");
        clearScreen();
      } else if(strcmp(arg[0],"immortalflames")){
        strcpy(company, "@Flames");
        clearScreen();
      } else if(strcmp(arg[0],"twinadder")){
        strcpy(company, "@Serpent");
        clearScreen();
      } else {
        printString("Unknown Grand Company\r\n");
      }
    ```
    Penjelasan:
    
    - Pengguna dapat mengetik grandcompany <nama> untuk bergabung.
    - Jika nama adalah:
      - maelstrom → company = "@Storm", terminal di-clear.
      - immortalflames → company = "@Flames", terminal di-clear.
      - twinadder → company = "@Serpent", terminal di-clear.
    - Jika nama tidak dikenali atau kosong → pesan error "Unknown Grand Company" muncul.
    - Nama company ditampilkan di shell prompt melalui fungsi info.
      
     2.Fungsi `clear`:
    ```c   
    } else if(strcmp(cmd,"clear")){
      strcpy(username,"user");
      strcpy(company,"");
      clearScreen();
    ```
    Penjelasan:
    - Saat pengguna mengetik clear, shell akan:
      - Mengembalikan username ke "user".
      - Menghapus nama Grand Company.
      - Membersihkan layar terminal.
   
     3.Fungsi `info`:
    ```c
    void info(char *username, char *company) {
      printString(username);
      printString(company);
      printString("> ");
    }
    ```
    Penjelasan:
    - Fungsi ini mencetak prompt shell seperti: username@GrandCompany>.
    - Misal: Tia@Storm>, user@Flames>, Alma@Serpent>, dsb.
    
---
5. Sebagai pahlawan terkenal di antara ketiga negara besar Eorzean Alliance, salah satu supplier senjata terbesar di seluruh Eorzea bernama "Rowena's House of Splendors" tiba-tiba memerlukan bantuan anda untuk membuat sebuah sistem kalkulator sederhana melalui command karena pemimpin mereka tertidur setelah mengurus semua orang di dalam Eorzea:
   * `add <x> <y>` = x + y
   * `sub <x> <y>` = x - y
   * `mul <x> <y>` = x * y
   * `div <x> <y>` = x / y

   Ilustrasi:
   ```
   user> add 4 2
   6
   user> sub 4 2
   2
   user> mul 3 -2
   -6
   user> div -6 -2
   3
   ```

   Jawab :

   Fungsi `shell`:

   Fungsi ini menangani perintah kalkulasi dari pengguna seperti add, sub, mul, dan div.

    ```c
    } else if(strcmp(cmd,"add")) {
      int num1, num2,result;
      char resultStr[64];
      if (arg[0][0] != '\0' && arg[1][0] != '\0') {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        result = num1 + num2;
        
        itoa(result, resultStr);       
        printString(resultStr);
        printString("\r\n");
      } else {
        printString("Usage: add <num1> <num2>\r\n");
      }
    }
    ```
    
      Penjelasan:
      - Jika pengguna mengetik add <num1> <num2>, maka:
      - Fungsi atoi() mengubah argumen string ke integer.
      - Operasi penjumlahan dilakukan dan hasilnya disimpan ke result.
      - Hasil dikonversi kembali ke string dengan itoa() lalu ditampilkan.
      - Fungsionalitas yang sama diterapkan pada sub, mul, dan div, hanya berbeda operator matematikanya.
      - Untuk div, ada tambahan pengecekan untuk mencegah pembagian dengan nol:
    ```c
    if (num2 == 0) {
      printString("Error: Division by zero\r\n");
    }
    ```
    Contoh Output:
    
    ```pgsql
    user> add 4 2
    6
    user> div 5 0
    Error: Division by zero
    ```
    
---    
6. me: yogurt
   
   gurt:
   * `yo`
   * `ts unami gng </3`
   * `sygau`

   pilih secara *random*

   Ilustrasi:
   ```
   user> yogurt
   gurt> yo
   user> yogurt
   gurt> ts unami gng </3
   user> yogurt
   gurt> sygau
   ```

   Jawab :

   Fungsi `shell`:

   Fungsi ini menangani perintah yogurt yang memberikan output acak dari tiga pilihan yang disiapkan.

    ```c
    } else if(strcmp(cmd,"yogurt")) {
      char response[3][100];
      int randomIndex;
      strcpy(response[0], "yo");
      strcpy(response[1], "ts unami gng </3");
      strcpy(response[2], "sygau");
      randomIndex = mod(getBiosTick(), 3); 
      printString(response[randomIndex]);
      printString("\r\n");
    }
    ```
      Penjelasan:
      - Perintah yogurt akan memilih salah satu dari tiga string secara acak:
        - "yo"
        - "ts unami gng </3"
        - "sygau"
      - Pemilihan acak untuk mengambil nilai dari getBiosTick() dan dihitung mod 3, agar hanya mendapat nilai 0, 1, atau 2 menggunakan: 
    ```c
    randomIndex = mod(getBiosTick(), 3);
    ```
    
    Contoh Output:
    
    ```shell
    user> yogurt
    gurt> yo
    user> yogurt
    gurt> sygau
    ```
---
7. Perusahaan mesin "Garlond Ironworks" tiba-tiba lelah mengurus permintaan senjata perang untuk orang ke-148649813234 yang berusaha menghadapi final boss yang sama, sehingga mereka perlu bantuan kamu untuk melengkapi `Makefile` yang diberikan dengan command-command yang sesuai untuk compile seluruh operating system ini.

## Petunjuk Soal

### Source

* [kernel.asm](src/kernel.asm)
  * `_putInMemory`: penjelasan terdapat dalam modul
  * `_interrupt`: fungsi untuk interrupt
    * `number`: interrupt vector number
    * `AX`,`BX`,`CX`,`DX`: register untuk diisi
    * `AX` merupakan kombinasi dari `AH` dan `AL`, pola ini juga berlaku untuk `BX`,`CX`, dan `DX`
    * Untuk menggabungkan jenis register `H` dan `L` menjadi `X` bisa menggunakan salah satu metode berikut:
      ```c
      AX = AH << 8 | AL    // first method
      AX = AH * 256 + AL   // second method
      ```
   * `getBiosTick`: fungsi untuk mendapatkan tick dari BIOS
* [kernel.c](src/kernel.c)
  * Diisi penerapan fungsi `printString`, `readString`, dan `clearScreen` dengan bantuan `kernel.asm`
    * untuk `printString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` dengan parameter `AH = 0x0E` untuk _teletype output_. Karakter yang ditampilkan dapat dimasukkan pada register `AL`. Fungsi ini akan menampilkan string karakter ASCII (_null-terminated_) ke layar.
    * untuk `readString`: Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 16h` dengan parameter `AH = 0x00` untuk _keyboard input_. Fungsi ini akan membaca karakter ASCII (_non-control_) yang dimasukkan oleh pengguna dan menyimpannya pada buffer hingga menekan tombol `Enter`. Handle tombol `Backspace` dibebaskan kepada praktikan.
    * untuk `clearScreen`: Ukuran layar adalah `80x25` karakter. Setelah layar dibersihkan, kursor akan kembali ke posisi awal yaitu `(0, 0)` dan buffer video untuk warna karakter diubah ke warna putih. Implementasi dapat menggunakan fungsi `interrupt` dengan service `int 10h` atau menggunakan fungsi `putInMemory` untuk mengisi memori video.
* [shell.c](src/shell.c)
  * Diisi penerapan shell yang menggunakan fungsi kernel untuk parsing keseluruhan command yang diinput

### Headers

* [std_type.h](include/std_type.h)
  * `byte`: unsigned char data type, untuk angka 0-255 (`0x00`-`0xFF`)
  * `bool`: untuk boolean (true/false), karena boolean tidak built-in
* [std_lib.h](include/std_lib.h)
  * `div`: division
  * `mod`: modulo
  * Pembagian dan modulo tidak ada dalam assembly, sehingga harus dilengkapi dengan operator yang tersedia (`+`,`-`,`*`,`<<`,`>>`)
  * `strcmp`: membandingkan dua string
  * `strcpy`: copy string
  * `clear`: fill memory dengan `0`
  * `atoi`: alphanumeric to integer (string menjadi angka)
  * `itoa`: integer to alphanumeric (angka menjadi string)
* [kernel.h](include/kernel.h)
  * Deklarasi header untuk fungsi-fungsi dalam `kernel.c`
* [shell.h](include/shell.h)
  * Deklarasi header untuk fungsi-fungsi dalam `shell.c`

### Makefile

* [makefile](./makefile)
   * `prepare` : membuat disk image baru `floppy.img` pada direktori `bin/` dengan ukuran 1.44 MB.
   * `bootloader` : mengkompilasi `bootloader.asm` menjadi `bootloader.bin` pada direktori `bin/`.
   * `stdlib` : mengkompilasi `std_lib.c` menjadi `std_lib.o` pada direktori `bin/`.
   * `shell`: mengkompilasi `shell.c` menjadi `shell.o` pada direktori `bin/`.
   * `kernel` : mengkompilasi `kernel.c` menjadi `kernel.o` pada direktori `bin/` dan mengkompilasi `kernel.asm` menjadi `kernel_asm.o` pada direktori `bin/`.
   * `link` : menggabungkan `bootloader.bin`, `kernel.o`, `kernel_asm.o`, dan `std_lib.o` menjadi `floppy.img`.
   * `build` : menjalankan perintah `prepare`, `bootloader`, `stdlib`, `kernel`, dan `link`.

### Video Demonstrasi

[Akses Video dalam Assets](./assets/demo.mp4)

https://github.com/user-attachments/assets/1cfa66b1-b2f5-4e3e-a4b2-ec8b012f6fbb


## Laporan
(-)
