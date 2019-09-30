//Copyright(c) 2011 - 2018 Kohe Tokoi.All Rights Reserved.
//
//Permission is hereby granted, free of charge, to any person obtaining a copy
//of this softwareand associated documentation files(the "Software"), to deal
//in the Software without restriction, including without limitation the rights
//to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
//copies or substantial portions of the Software.
//
//The above  copyright noticeand this permission notice  shall be included in
//all copies or substantial portions of the Software.
//
//THE SOFTWARE  IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//IMPLIED, INCLUDING  BUT  NOT LIMITED  TO THE WARRANTIES  OF MERCHANTABILITY,
//FITNESS  FOR  A PARTICULAR PURPOSE  AND NONINFRINGEMENT.IN  NO EVENT  SHALL
//KOHE TOKOI  BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
//AN ACTION  OF CONTRACT, TORT  OR  OTHERWISE, ARISING  FROM, OUT OF  OR  IN
//CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#pragma once

//
// ウィンドウ関連の処理
//
class Window
{
  // ウィンドウの識別子
  GLFWwindow *const window;

  // ウィンドウのサイズ
  GLfloat size[2];

  // ワールド座標系に対するデバイス座標系の拡大率
  GLfloat scale;

public:

  // コンストラクタ
  Window(int width = 640, int height = 480, const char *title = "Untitled")
    : window(glfwCreateWindow(width, height, title, NULL, NULL))
    , scale(100.0f)
  {
    if (window == NULL)
    {
      // ウィンドウが作成できなかった
      std::cerr << "Can't create GLFW window." << std::endl;
      exit(1);
    }

    // 現在のウィンドウを処理対象にする
    glfwMakeContextCurrent(window);

    // GLEW を初期化する
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
      // GLEW の初期化に失敗した
      std::cerr << "Can't initialize GLEW" << std::endl;
      exit(1);
    }

    // 作成したウィンドウに対する設定
    glfwSwapInterval(1);

    // ウィンドウのサイズ変更時に呼び出す処理の登録
    glfwSetWindowSizeCallback(window, resize);

    // このインスタンスの this ポインタを記録しておく
    glfwSetWindowUserPointer(window, this);

    // 開いたウィンドウの初期設定
    resize(window, width, height);
  }

  // デストラクタ
  virtual ~Window()
  {
    // ウィンドウを破棄する
    glfwDestroyWindow(window);
  }

  // 描画ループの継続判定
  explicit operator bool()
  {
    // イベントを取り出す
    glfwPollEvents();

    // ウィンドウを閉じる必要がなければ true を返す
    return !glfwWindowShouldClose(window);
  }

  // ダブルバッファリング
  void swapBuffers() const
  {
    // カラーバッファを入れ替える
    glfwSwapBuffers(window);
  }

  // ウィンドウのサイズ変更時の処理
  static void resize(GLFWwindow *window, int width, int height)
  {
    // フレームバッファの大きさを得る
    int fbWidth, fbHeight;
    glfwGetFramebufferSize(window, &fbWidth, &fbHeight);
    
    // フレームバッファ全体をビューポートにする
    glViewport(0, 0, fbWidth, fbHeight);

    // このインスタンスの this ポインタを得る
    Window *const
      instance(static_cast<Window *>(glfwGetWindowUserPointer(window)));

    if (instance != NULL)
    {
      // 開いたウィンドウのサイズを保存する
      instance->size[0] = static_cast<GLfloat>(width);
      instance->size[1] = static_cast<GLfloat>(height);
    }
  }

  // ウィンドウのサイズを取り出す
  const GLfloat *getSize() const { return size; }

  // ワールド座標系に対するデバイス座標系の拡大率を取り出す
  GLfloat getScale() const { return scale; }
};
