# Makefile

# プログラム名とオブジェクトファイル名
program = Triangle
objs = Triangle.o shader_utils.o

# 定義済マクロの再定義
CC = g++
CFLAGS =
LDLIBS =-lglut -lGLEW -lGL

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
shader_utils.o: shader_utils.h
