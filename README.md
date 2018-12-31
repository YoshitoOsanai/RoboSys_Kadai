# RoboSys2018
+ これは千葉工業大学先進工学部未来ロボティクス学科学部三年、ロボットシステム学の課題１です。

## 概要
+ RaspberryPiのGPIOピンを用いたデバイスドライバを作成する。
+ 5つのLEDを制御する。

## 環境
+ RaspberryPi3 Model B V1.2
+ Ubuntu 18.04.1 LTS

## 結果
+ [YouTube](https://www.youtube.com/watch?v=qrRTR4KlN3s)

## 実行方法
### メイクおよびモジュールの追加
```Bash
sudo ./devsetup.bash
```

### LEDの操作
```Bash
echo 1 > /dev/myled0  #GPIO 23
echo 2 > /dev/myled0  #GPIO 22
echo 3 > /dev/myled0  #GPIO 25
echo 4 > /dev/myled0  #GPIO 18
echo 5 > /dev/myled0  #GPIO  4
echo 0 > /dev/myled0  #Turn off
```

### ウェーブ状に点灯
```Bash
./wave.bash
```
