c-library
---------

## これは何？

C標準ライブラリの実装を試みています。
通常のOSが使えず、普通のC標準ライブラリが使えない環境を想定しています。

## ビルド方法は？

ライブラリ本体

```
$ make
```

テスト

```
$ make test
```

テストを行うには、[CppUnit](https://sourceforge.net/projects/cppunit/)がインストールされて
(コンパイルオプションでパスを指定しなくてもコンパイル・リンクできる状態で)ないといけません。

## What is this?

Trying to implement the C standard library.
For usual OS is not available and normal C standard library cannot be used.

## How to build?

The library itself

```
$ make
```

Test

```
$ make test
```

It is required that [CppUnit](https://sourceforge.net/projects/cppunit/) is installed
(available without specifying paths in compiler options) to do testing.
