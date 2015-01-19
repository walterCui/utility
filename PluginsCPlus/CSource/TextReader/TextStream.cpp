//
//  TextStream.cpp
//  EPet
//
//  Created by walter on 14/10/31.
//  Copyright (c) 2014年 com.Example. All rights reserved.
//

#include "TextStream.h"

//rowCell
rowCell::rowCell(int col,int rowId):colNum(col), id(rowId)
{
    if(col <= 0)
        return;
    titles = new char*[col];
    values = new char*[col];
    for(int i = 0; i < col; i++)
    {
        titles[i] = NULL;
        values[i] = NULL;
    }
}

rowCell::rowCell(rowCell *cell)
{
    if(cell == NULL)
        return;
    this->id = cell->id;
    this->colNum = cell->colNum;
    if(this->colNum > 0)
    {
        titles = new char*[colNum];
        values = new char*[colNum];
        for(int i = 0; i < colNum; i++)
        {
            if(cell->titles[i] != NULL)
            {
                titles[i] = new char[strlen(cell->titles[i])+1];
                strcpy(titles[i], cell->titles[i]);
            }
            if(cell->values[i] != NULL)
            {
                values[i] = new char[strlen(cell->values[i])+1];
                strcpy(values[i], cell->values[i]);
            }
        }
    }
}
rowCell::~rowCell()
{
    if(colNum > 0)
    {
        for(int i = 0; i < colNum; i++)
        {
            if(titles[i] != NULL)
            {
                delete [] titles[i];
            }
            if(values[i] != NULL)
            {
                delete [] values[i];
            }
        }
        delete [] titles;
        delete [] values;
    }
}

void rowCell::add(int index, char *val, char *title)
{
    if(index < 0 || index >= colNum || val == NULL)
        return;
    values[index] = new char[strlen(val)+1];
    strcpy(values[index], val);
    
    if(title != NULL)
    {
        titles[index] = new char[strlen(title)+1];
        strcpy(titles[index], title);
    }
}

void rowCell::setTitle(int index, char *title)
{
    if(index < 0 || index >= colNum)
        return;
    if(title != NULL)
    {
        titles[index] = new char[strlen(title)+1];
        strcpy(titles[index], title);
    }

}

const char* rowCell::getTitle(int index)
{
    if(index < 0 || index >= colNum || titles[index] == NULL)
        return "";
    return titles[index];
}

const char* rowCell::getValue(int index)
{
    if(index < 0 || index >= colNum || values == NULL || values[index] == NULL)
        return "";
    
    return values[index];
}

const char* rowCell::getValue(const char *title)
{
    if(title == NULL)
        return NULL;
    
    for(int i = 0; i < colNum; i++)
    {
        if(strcmp(title, titles[i]) == 0)
            return values[i];
    }
    return  NULL;
}

int rowCell::getValueInt(int index)
{
    if(index < 0 || index >= colNum || values[index] == NULL)
        return 0;
    
    return  atoi(values[index]);
}

int rowCell::getValueInt(const char *title)
{
    
    if(title == NULL)
        return 0;
    
    for(int i = 0; i < colNum; i++)
    {
        if(strcmp(title, titles[i]) == 0)
            return atoi(values[i]);
    }
    return  0;

}

//TextStream
TextStream::TextStream(const char *textPath, int baseId):inFile(textPath, std::ios_base::in)
{
    
    colNum = 0;
    rowNum = 0;
    
    if( inFile.fail())
    {
        inFile.close();
        throw TextStreamException(strcat((char*)"[Error]the file not find:",textPath));
    }
    else
    {
        int buffLen = 1024;
        char *buff = new char[buffLen];
        
        //计算有多少列并纪录title.
        inFile.getline(buff, buffLen);
        if(inFile.fail())
        {
            throw TextStreamException((char*)"get line error");
        }
        
        char * split = (char*)",";
        char *tokenPtr = strtok(buff, split);
        while (tokenPtr) {
            title[colNum] = new char[strlen(tokenPtr)+1];
            strcpy(title[colNum], tokenPtr);
            colNum++;
            if(colNum >= MAXCOLNUM)
                break;
            tokenPtr = strtok(NULL, split);
        }
        
        content = new rowCell*[MAXROWNUM];
        //inFile.getline(buff, buffLen);
        while (!inFile.eof()) {
            if(inFile.getline(buff, buffLen).bad() && !inFile.std::ios_base::eof())
                break;
            content[rowNum] = new rowCell(colNum,rowNum);
                content[rowNum]->id = rowNum + baseId;
            tokenPtr = strtok(buff, split);
            for(int i = 0; i < colNum; i++)
            {
                content[rowNum]->add(i, tokenPtr, NULL);
                tokenPtr = strtok(NULL, split);
            }
            rowNum++;
            if(rowNum >= MAXROWNUM)
                break;
            //inFile.getline(buff, buffLen);
        }
        
        
        delete [] buff;
    }
}

TextStream::~TextStream()
{
    for(int i = 0; i < colNum; i++)
        delete title[i];
    
    for(int i = 0; i < rowNum; i++)
        delete content[i];
    
    delete [] content;
}

rowCell* TextStream::getRow(int index)
{
    if(index < 0 || index >= rowNum)
        return NULL;
    if(content[index] == NULL)
        return  NULL;
    rowCell *ret = new rowCell(content[index]);
    for(int i= 0; i < colNum; i++)
    {
        ret->setTitle(i, title[i]);
    }
    return  ret;
}
/*
int TextStream::getRowNum()
{
    return rowNum;
}*/

//exception.

TextStreamException::TextStreamException(char* msg)
{
    what = msg;
}

TextStreamException::~TextStreamException() throw()
{
    
}

const char* TextStreamException::What() const throw()
{
    return what;
}