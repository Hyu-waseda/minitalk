# minitalk (Lv.2)

シグナル通信用のサーバーとクライアントの作成

# Usage

・実行ファイル`server`と`client`の作成

```bash
make
```

・作成された`server`を実行

```bash
./server
10057
```

・別の端末やターミナル等で`client`を実行
・引数にserverのpid、送信文字列を渡す

Example:
```bash
./client 10057 hogehoge
```
