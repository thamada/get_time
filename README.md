# get_time

時間測定用C関数

## Build run.x as a test app.

```
make
```

## Run the test app.


```
./run.x
```

## for more detailed

Please read main.c

## 説明

get_time, get_time_utime, get_time_wctime:

時間を測定する目的で使用されますが、その動作や測定対象の時間が異なり
ます。

get_time_utime関数とget_time_wctime関数はどちらも時間を測定する目的で
使用されますが、その動作や測定対象の時間が異なります。それぞれの違いを
以下に詳しく説明します。

### 0. 要約

get_time_utime 関数 は、プログラムが実際に計算に費やしたユーザーCPU時
間を秒単位で取得します。

get_time_wctime 関数 は、実世界の経過時間（wall-clock time）を秒単位で
取得し、プログラム全体の実行時間を測定するために使用されます。


### 1. 測定対象の違い

#### get_time_utime 関数:

getrusage 関数を使用して、現在のプロセスのユーザーCPU時間を秒単位で取
得します。CPUが実際に計算に費やした時間のみを測定します。つまり、I/O待
ち時間やスリープ時間などは含まれません。この関数はプログラムの処理効率
を測定するのに適しています。

#### get_time_wctime 関数:

clock_gettime 関数を使用して、実時間（リアルタイム）をミリ秒単位で取得
します。CLOCK_REALTIME を使用しているため、実世界の時間、つまりカレン
ダー時間を返します。この時間にはプログラムの実行中に経過したすべての時
間が含まれ、CPUが処理していない待機時間も含まれます。この関数は、プロ
グラム全体の実行時間を測定するのに適しています。

### 2. 時間の計算方法

#### get_time_utime 関数:
struct rusage を使用して、秒（tv_sec）とマイクロ秒（tv_usec）を取り出
し、それらを合わせて秒単位の時間を計算します。

#### get_time_wctime 関数:

struct timespec を使用し、clock_gettime で取得した時刻の秒（tv_sec）を
ミリ秒に変換し、ナノ秒（tv_nsec）をミリ秒に変換して加算します。時間を
ミリ秒単位で計算し、それをさらに秒に変換しています。

### 3. 返り値の精度

#### get_time_utime 関数:

秒単位の高精度なCPU使用時間を返します（マイクロ秒の精度を持つ）。

#### get_time_wctime 関数:

ミリ秒単位で実時間を取得し、それを秒に変換して返します（ミリ秒の精度）。


## GNU拡張について

_POSIX_C_SOURCEは-std=c99オプションを使ってコンパイルできるようにする
ためにあります。

コンパイルが失敗する理由は、-std=c99オプションを使った際に、
clock_gettime関数とCLOCK_REALTIME定数が使用できないためです。C99規格は
標準ライブラリの中で一部の機能をサポートしていませんが、GNU拡張
（-std=gnu99）を使うと標準Cライブラリに含まれないいくつかのPOSIX関数が
利用可能になります。

具体的には、以下の理由でエラーが発生します：

### struct timespecの未定義:

C99規格では、<time.h>はstruct timespecを定義していない可能性があります。
そのため、struct timespecのサイズが不明なためコンパイルが失敗します。

### clock_gettime関数の未宣言:

clock_gettime関数はPOSIXに準拠している関数であり、C99の標準には含まれ
ていません。そのため、C99でコンパイルすると「暗黙の宣言」という警告が
発生し、関数のプロトタイプが見つからないためコンパイルが失敗します。

### CLOCK_REALTIMEの未定義:

CLOCK_REALTIMEもPOSIX定数であり、C99標準では宣言されていません。そのた
め、未定義エラーが発生します。

解決策

これらのエラーを解決するには、次のいずれかの方法を使用できます：

### 1. POSIX準拠のオプションを使用する:

    -std=gnu99や-std=gnu11を使用すると、POSIX関数が利用可能になります。こ
    れにより、clock_gettimeやCLOCK_REALTIMEの定義が有効になります。

```
gcc -Wall -Ofast -std=gnu99 -c get_time.c 
```

### 2. POSIX機能を有効にするために、POSIX定数_POSIX_C_SOURCEを宣言する

    POSIX定数_POSIX_C_SOURCEを宣言することで、C99モードでも
    clock_gettimeが使用可能になります。

今回は2.の方法を使っています。
