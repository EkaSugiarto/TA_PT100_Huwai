// #include <HTTPClient.h> // Tambahkan ini

// void sendDataToMySQL(float suhu1, float suhu2) {
//   if (WiFi.status() == WL_CONNECTED) {
//     HTTPClient http; // Deklarasi objek dari kelas HTTPClient

//     String serverPath = "https://autecalibration.iot4environment.com/insert_data.php" + String(kalibrasiSuhu1, 4) + "&suhu2=" + String(Suhu2, 4);

//     http.begin(serverPath.c_str());    // Spesifikasikan tujuan permintaan
//     int httpResponseCode = http.GET(); // Mengirim permintaan

//     if (httpResponseCode > 0) {
//       String payload = http.getString(); // Dapatkan respon permintaan
//       Serial.println(httpResponseCode);  // Cetak kode return HTTP
//       Serial.println(payload);           // Cetak respon permintaan
//     } else {
//       Serial.print("Error on sending GET Request: ");
//       Serial.println(httpResponseCode);
//     }
//     http.end(); // Bebaskan sumber daya
//   } else {
//     Serial.println("WiFi Disconnected");
//   }
// }
