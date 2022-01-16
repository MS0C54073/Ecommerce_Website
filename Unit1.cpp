//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdio>

#include "Unit1.h"
#include "shen_fano.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

char *rotlexcmp_buf = NULL;
int rottexcmp_bufsize = 0;

int rotlexcmp(const void *l, const void *r)
{
    int li = *(const int*)l, ri = *(const int*)r, ac=rottexcmp_bufsize;
    while (rotlexcmp_buf[li] == rotlexcmp_buf[ri])
    {
        if (++li == rottexcmp_bufsize)
            li = 0;
        if (++ri == rottexcmp_bufsize)
            ri = 0;
        if (!--ac)
            return 0;
    }
    if (rotlexcmp_buf[li] > rotlexcmp_buf[ri])
        return 1;
    else
        return -1;
}

void TForm1::BWT_encode(char *buf_in, char *buf_out, int size, int *primary_index)
{
    int indices[size];
    int i;

    for(i=0; i<size; i++)
        indices[i] = i;
    rotlexcmp_buf = buf_in;
    rottexcmp_bufsize = size;
	qsort (indices, size, sizeof(int), rotlexcmp);

    for (i=0; i<size; i++)
        buf_out[i] = buf_in[(indices[i]+size-1)%size];
    for (i=0; i<size; i++)
    {
        if (indices[i] == 1) {
            *primary_index = i;
            return;
        }
    }
    assert (0);
}

void TForm1::BWT_decode(char *buf_in, char *buf_out, int size, int primary_index)
{
	char F[size];
    int buckets[256];
    int i,j,k;
    int indices[size];

    for (i=0; i<256; i++)
        buckets[i] = 0;
    for (i=0; i<size; i++)
        buckets[buf_in[i]] ++;
    for (i=0,k=0; i<256; i++)
        for (j=0; j<buckets[i]; j++)
            F[k++] = i;
    assert (k==size);
    for (i=0,j=0; i<256; i++)
    {
        while (i>F[j] && j<size)
            j++;
        buckets[i] = j; // it will get fake values if there is no i in F, but
                        // that won't bring us any problems
    }
    for(i=0; i<size; i++)
        indices[buckets[buf_in[i]]++] = i;
    for(i=0,j=primary_index; i<size; i++)
    {
        buf_out[i] = buf_in[j];
        j=indices[j];
    }
}

void TForm1::RLE_compress(std::ifstream &file, std::ofstream &file_compr)
{
	char sym; //символ, который мы будем считывать
	int kol=1;// количество повтор€ющихс€ символов

	file.seekg( 0, std::ios::end );
	int fsize = file.tellg();
	file.seekg( 0, std::ios::beg );
	int cur = 0;
    while(file.good())
	{
		cur++;
		file.get(sym);//считываем символ
		pb_progress->Position =cur / (fsize / 100.0);
		Application->ProcessMessages();
		if(sym != file.peek() || kol==9) // если символ не совпадает со следующим символом в файле
		{
			file_compr << kol << sym; // записываем результаты в выходной файл
            kol=0;
        }
        kol++;
	}
}

void TForm1::RLE_compress(std::string &context, std::ofstream &file_compr)
{
	char sym; //символ, который мы будем считывать
	int kol=1;// количество повтор€ющихс€ символов

	int fsize = context.size();
	int cur = 0;
    while(cur < fsize)
	{
		sym = context.at(cur);
		cur++;
		pb_progress->Position =cur / (fsize / 100.0);
		Application->ProcessMessages();
		if((cur + 1) >= fsize || sym != context.at(cur + 1) || kol==9) // если символ не совпадает со следующим символом в файле
		{
			file_compr << kol << sym; // записываем результаты в выходной файл
            kol=0;
        }
        kol++;
	}
}

void TForm1::RLE_decompress(std::ifstream &file, std::ofstream &file_decompr)
{
	char sym1,sym2; // предыдущий и последующий символы
    const char zero = '0';
	while(file.peek()!=EOF)
    {
		file.get(sym1);
        file.get(sym2);
        for(int i=0; i < sym1 - zero; i++)
            file_decompr << sym2;
	}
}

void TForm1::RLE_decompress(std::ifstream &file, std::string &context)
{
	char sym1,sym2; // предыдущий и последующий символы
    const char zero = '0';
	while(file.peek()!=EOF)
	{
		file.get(sym1);
        file.get(sym2);
        for(int i=0; i < sym1 - zero; i++)
            context.push_back(sym2);
	}
}
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	   cmb_compress_type->AddItem("RLE", nullptr);
	   cmb_compress_type->AddItem("RLE BWT", nullptr);
       cmb_compress_type->AddItem("Entropy", nullptr);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btn_browse_srcClick(TObject *Sender)
{
	if (OpenFileDlg->Execute())
	{
		edit_src_path->Text = OpenFileDlg->FileName;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btn_browse_destClick(TObject *Sender)
{
	if (SaveDialog->Execute())
	{
		edit_dest_path->Text = SaveDialog->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_browse_dest_unpackClick(TObject *Sender)
{
	if (SaveDialog->Execute())
	{
		edit_dest_unpack->Text = SaveDialog->FileName;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_browse_archClick(TObject *Sender)
{
	if (OpenFileDlg->Execute())
	{
		edit_arch->Text = OpenFileDlg->FileName;
	}
}
//---------------------------------------------------------------------------


void __fastcall TForm1::btn_packClick(TObject *Sender)
{
	pb_progress->Position = 0;
	Application->ProcessMessages();

	String path_file_src = edit_src_path->Text;
	String path_file_dest = edit_dest_path->Text;

	std::ifstream file_src(path_file_src.c_str());
	if(!file_src.is_open())
		return;

	std::ofstream file_dest(path_file_dest.c_str());
	if(!file_dest.is_open())
		return;

	// write signature data to output file
	if (chkbox_set_pwd->Checked) {
		std::wstring pass = edit_pwd->Text.c_str();
		file_dest << "pwd";
		if (pass.size() < 10)
			file_dest << "0" << pass.size();
		else
			file_dest << pass.size();
		file_dest <<  std::string(pass.begin(), pass.end());
	}

	if (cmb_compress_type->ItemIndex == 0) { // RLE
		// Write sign
        file_dest << "RLE";
        // compress
		RLE_compress(file_src, file_dest);
	}
	else if (cmb_compress_type->ItemIndex == 1) { // RLE with BWT
		// Write sign
		file_dest << "BWT";
		std::string in_str((std::istreambuf_iterator<char>(file_src)),
				 std::istreambuf_iterator<char>());
		std::string out_str;
		out_str.resize(in_str.size());
		int primary_index;
		BWT_encode(&*in_str.begin(), &*out_str.begin(), in_str.size(), &primary_index);
		file_dest<< std::setfill('0') << std::setw(4)<< primary_index;
		// RLE
		RLE_compress(out_str, file_dest);
	}
	else if (cmb_compress_type->ItemIndex == 2) { // Entropy encoding (Shannon-Fano)
		Coder *coder = new Coder;
		std::string inputFile( path_file_src.begin(), path_file_src.end());
		std::string outputFile( path_file_dest.begin(), path_file_dest.end());
		coder->Encode( inputFile.c_str(), outputFile.c_str() );
		delete coder;
	}


	file_src.close();
	file_dest.close();

    if (chkbox_del_src->Checked) {
		DeleteFile(path_file_src.c_str());
	}

    pb_progress->Position = 0;
	Application->ProcessMessages();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btn_unpackClick(TObject *Sender)
{
	String path_file_src = edit_arch->Text;
	String path_file_dest = edit_dest_unpack->Text;

	std::ifstream file_src(path_file_src.c_str());
	if(!file_src.is_open())
		return;

	std::ofstream file_dest(path_file_dest.c_str());
	if(!file_dest.is_open())
		return;

	// read signature
	char pwd_sign[4];
	file_src.get(pwd_sign, 4);
	if (strcmp(pwd_sign, "pwd") == 0) {
		// read pass len
		char pwd_len[3];
		file_src.get(pwd_len, 3);
		int len = std::atoi(pwd_len);
		// read pass
		char pass[len + 1];
		file_src.get(pass, len + 1);
		// ask password
		AnsiString InputPwd = InputBox("Enter password", "Pass", "");
		if (strcmp(pass, InputPwd.c_str()) != 0) {
			Application->MessageBox(L"Incorrect password", L"Error", MB_OK);
            return;
		}
	}
	else
		file_src.seekg( 0, std::ios::beg );

	// read compress signature
	char compress_sign[4];
	file_src.get(compress_sign, 4);

	if (strcmp(compress_sign, "RLE") == 0) {
		RLE_decompress(file_src, file_dest);
	}
	else if (strcmp(compress_sign, "BWT") == 0) {
		// read primary_index
		char prim[5];
		file_src.get(prim, 5);
		int primary_index = atoi(prim);
		// RLE
		std::string in_str;
		RLE_decompress(file_src, in_str);
		// BWT decode
		std::string out_str;
		out_str.resize(in_str.size());
		BWT_decode(&*in_str.begin(), &*out_str.begin(), in_str.size(), primary_index);
		file_dest << out_str;
	}
	else // Shannon-Fano
	{
        Coder *coder = new Coder;
		std::string inputFile( path_file_src.begin(), path_file_src.end());
		std::string outputFile( path_file_dest.begin(), path_file_dest.end());
		coder->Decode( inputFile.c_str(), outputFile.c_str() );
		delete coder;
    }

	file_src.close();
	file_dest.close();
}
//---------------------------------------------------------------------------


