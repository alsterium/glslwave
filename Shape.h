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
#include <memory>

// 図形データ
#include "Object.h"

//
// 図形の描画
//
class Shape
{
  // 図形データ
  std::shared_ptr<const Object> object;

protected:

  // 描画に使う頂点の数
  const GLsizei vertexcount;

public:

  // コンストラクタ
  //   size: 頂点の位置の次元
  //   vertexcount: 頂点の数
  //   vertex: 頂点属性を格納した配列
  Shape(GLint size, GLsizei vertexcount, const Object::Vertex *vertex)
    : object(new Object(size, vertexcount, vertex))
    , vertexcount(vertexcount)
  {
  }

  // 描画
  void draw() const
  {
    // 頂点配列オブジェクトを結合する
    object->bind();

    // 描画を実行する
    execute();
  }

  // 描画の実行
  virtual void execute() const
  {
    // 折れ線で描画する
    glDrawArrays(GL_TRIANGLE_FAN, 0, vertexcount);
  }
};
