//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *edit_dest_path;
	TEdit *edit_src_path;
	TButton *btn_browse_src;
	TButton *btn_browse_dest;
	TLabel *Label3;
	TComboBox *cmb_compress_type;
	TCheckBox *chkbox_del_src;
	TCheckBox *chkbox_set_pwd;
	TEdit *edit_pwd;
	TProgressBar *pb_progress;
	TGroupBox *GroupBox2;
	TButton *btn_pack;
	TLabel *Label4;
	TEdit *edit_arch;
	TButton *btn_browse_arch;
	TLabel *Label5;
	TEdit *edit_dest_unpack;
	TButton *btn_browse_dest_unpack;
	TButton *btn_unpack;
	TOpenTextFileDialog *OpenFileDlg;
	TSaveDialog *SaveDialog;
	void __fastcall btn_browse_srcClick(TObject *Sender);
	void __fastcall btn_browse_destClick(TObject *Sender);
	void __fastcall btn_browse_dest_unpackClick(TObject *Sender);
	void __fastcall btn_browse_archClick(TObject *Sender);
	void __fastcall btn_packClick(TObject *Sender);
	void __fastcall btn_unpackClick(TObject *Sender);
private:	// User declarations
	void RLE_compress(std::ifstream &file, std::ofstream &file_compr);
	void RLE_compress(std::string &context, std::ofstream &file_compr);
	void RLE_decompress(std::ifstream &file, std::ofstream &file_decompr);
	void RLE_decompress(std::ifstream &file, std::string &context);
	void BWT_encode(char *buf_in, char *buf_out, int size, int *primary_index);
    void BWT_decode(char *buf_in, char *buf_out, int size, int primary_index);
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
