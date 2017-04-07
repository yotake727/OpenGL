# Makefile

# プログラム名とオブジェクトファイル名
program = Line
objs = Line.o

# 定義済マクロの再定義
CC = g++
CFLAGS =
LDLIBS =-lglut -lGLEW -lGL -lm

# サフィックスルール適用対象の拡張子の定義
.SUFFIXES: .c .o

# プライマリターゲット
$(program): $(objs)
	$(CC) -o $(program) $^ $(LDLIBS)

# サフィックスルール
.c.o:
	$(CC) $(CFLAGS)-c $<

# ファイル削除用ターゲット
.PHONY: clean
clean:
	$(RM) $(program) $(objs)

# ヘッダーファイルの依存関係
# main.o: main.h
