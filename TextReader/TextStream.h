//
//  TextStream.h
//  EPet
//
//  Created by walter on 14/10/31.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#ifndef __EPet__TextStream__
#define __EPet__TextStream__

#include <stdio.h>
#include <fstream>

#define MAXCOLNUM 64
#define MAXROWNUM 1024

class rowCell;

class TextStream
{
public:
    TextStream(const char *textPath);
    ~TextStream();
    
    rowCell* getRow(int index);
    
    inline int getColNum()
    {
        return  colNum;
    }
    
    inline int getRowNum()
    {
        return rowNum;
    }
private:
    int colNum;
    int rowNum;
    char *title[MAXCOLNUM];
    rowCell **content;
    char *path;
    std::ifstream inFile;
};

class rowCell
{
    friend class TextStream;
public:
    rowCell(int col,int rowId);
    rowCell(rowCell *cell);
    ~rowCell();
    
    void add(int index, char *val, char *title);
    
    inline int Id()
    {
        return id;
    }
    
    const char* getTitle(int index);
    
    const char* getValue(int index);
    
    const char* getValue(const char *title);
    
    int getValueInt(int index);
    
    int getValueInt(const char *title);
private:
    void setTitle(int index, char *title);
    
private:
    int id;
    int colNum;
    char **titles;
    char **values;
};

class TextStreamException:public std::exception
{
public:
    TextStreamException(char* msg);
    ~TextStreamException()throw();
    virtual const char* What() const throw();
private:
    char *what;
};

#endif /* defined(__EPet__TextStream__) */
