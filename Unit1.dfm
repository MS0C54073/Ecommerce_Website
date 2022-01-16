object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 297
  ClientWidth = 641
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  DesignSize = (
    641
    297)
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 625
    Height = 161
    Anchors = [akLeft, akTop, akRight]
    Caption = 'Compress'
    TabOrder = 0
    DesignSize = (
      625
      161)
    object Label1: TLabel
      Left = 8
      Top = 18
      Width = 50
      Height = 13
      Caption = 'Source file'
    end
    object Label2: TLabel
      Left = 8
      Top = 49
      Width = 71
      Height = 13
      Caption = 'Destination file'
    end
    object Label3: TLabel
      Left = 8
      Top = 83
      Width = 72
      Height = 13
      Caption = 'Compress type'
    end
    object edit_dest_path: TEdit
      Left = 85
      Top = 46
      Width = 463
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ReadOnly = True
      TabOrder = 0
    end
    object edit_src_path: TEdit
      Left = 85
      Top = 15
      Width = 463
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ReadOnly = True
      TabOrder = 1
    end
    object btn_browse_src: TButton
      Left = 552
      Top = 13
      Width = 70
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Browse...'
      TabOrder = 2
      OnClick = btn_browse_srcClick
    end
    object btn_browse_dest: TButton
      Left = 552
      Top = 44
      Width = 70
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Browse...'
      TabOrder = 3
      OnClick = btn_browse_destClick
    end
    object cmb_compress_type: TComboBox
      Left = 86
      Top = 80
      Width = 178
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 4
    end
    object chkbox_del_src: TCheckBox
      Left = 296
      Top = 82
      Width = 97
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Delete sources'
      TabOrder = 5
      WordWrap = True
    end
    object chkbox_set_pwd: TCheckBox
      Left = 399
      Top = 82
      Width = 97
      Height = 17
      Anchors = [akTop, akRight]
      Caption = 'Set password'
      TabOrder = 6
    end
    object edit_pwd: TEdit
      Left = 486
      Top = 80
      Width = 136
      Height = 21
      Anchors = [akTop, akRight]
      TabOrder = 7
    end
    object pb_progress: TProgressBar
      Left = 3
      Top = 107
      Width = 619
      Height = 16
      Anchors = [akLeft, akTop, akRight]
      TabOrder = 8
    end
    object btn_pack: TButton
      Left = 272
      Top = 129
      Width = 87
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Pack'
      TabOrder = 9
      OnClick = btn_packClick
    end
  end
  object GroupBox2: TGroupBox
    Left = 8
    Top = 173
    Width = 625
    Height = 116
    Anchors = [akLeft, akTop, akRight, akBottom]
    Caption = 'Decompress'
    TabOrder = 1
    DesignSize = (
      625
      116)
    object Label4: TLabel
      Left = 3
      Top = 24
      Width = 42
      Height = 13
      Caption = 'Archieve'
    end
    object Label5: TLabel
      Left = 3
      Top = 56
      Width = 54
      Height = 13
      Caption = 'Destination'
    end
    object edit_arch: TEdit
      Left = 85
      Top = 21
      Width = 463
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ReadOnly = True
      TabOrder = 0
    end
    object btn_browse_arch: TButton
      Left = 552
      Top = 19
      Width = 70
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Browse...'
      TabOrder = 1
      OnClick = btn_browse_archClick
    end
    object edit_dest_unpack: TEdit
      Left = 85
      Top = 53
      Width = 463
      Height = 21
      Anchors = [akLeft, akTop, akRight]
      ReadOnly = True
      TabOrder = 2
    end
    object btn_browse_dest_unpack: TButton
      Left = 552
      Top = 51
      Width = 70
      Height = 25
      Anchors = [akTop, akRight]
      Caption = 'Browse...'
      TabOrder = 3
      OnClick = btn_browse_dest_unpackClick
    end
    object btn_unpack: TButton
      Left = 272
      Top = 80
      Width = 87
      Height = 25
      Anchors = [akLeft, akTop, akRight]
      Caption = 'Unpack'
      TabOrder = 4
      OnClick = btn_unpackClick
    end
  end
  object OpenFileDlg: TOpenTextFileDialog
    Left = 40
    Top = 245
  end
  object SaveDialog: TSaveDialog
    Left = 104
    Top = 245
  end
end
