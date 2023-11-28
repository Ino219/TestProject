#include "MyForm.h"

using namespace TestProject;
using namespace System::Collections::Generic;
using namespace System::IO;

[STAThreadAttribute]

int main() {
	Application::Run(gcnew MyForm());
	return 0;
}

System::Void TestProject::MyForm::button1_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog(1);
	return System::Void();
}

System::Void TestProject::MyForm::button2_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	cli::array<String^>^ tmparray = gcnew cli::array<String^>{textBox1->Text,textBox2->Text};
	cli::array<List<String^>^>^ arrayList = gcnew  cli::array<List<String^>^>(2);

	for (int j = 0; j < tmparray->Length; j++) {
		String^ fullPath = tmparray[j];
		String^ Dext = getDeleteExtension(fullPath);
		String^ Dtail = getDeleteTail(Dext);

		//ディレクトリ名の取得
		String^ DirName = System::IO::Path::GetDirectoryName(fullPath);
		cli::array<String^>^ allFile = Directory::GetFiles(DirName);
		List<String^>^ arr = gcnew List<String^>;

		for (int i = 0; i < allFile->Length; i++) {
			//ファイル名取得
			String^ fileName = allFile[i];
			String^ f_Dext = getDeleteExtension(fileName);
			String^ f_Dtail = getDeleteTail(f_Dext);
			//改名後ファイル名の取得
			if (f_Dtail == Dtail) {
				arr->Add(fileName);

			}
		}
		if (arr->Count != 0) {
			arrayList[j] = arr;
		}
	}


	return System::Void();
}

System::Void TestProject::MyForm::openFileDialog(int index)
{
	OpenFileDialog^ ofd = gcnew OpenFileDialog();

	//はじめのファイル名を指定する
	//はじめに「ファイル名」で表示される文字列を指定する
	ofd->FileName = "default.html";
	//はじめに表示されるフォルダを指定する
	//指定しない（空の文字列）の時は、現在のディレクトリが表示される
	ofd->InitialDirectory = "C:\\Users\\chach\\Desktop\\ffolder";
	//[ファイルの種類]に表示される選択肢を指定する
	//指定しないとすべてのファイルが表示される
	ofd->Filter = "HTMLファイル(*.html;*.htm)|*.html;*.htm|すべてのファイル(*.*)|*.*";
	//[ファイルの種類]ではじめに選択されるものを指定する
	//2番目の「すべてのファイル」が選択されているようにする
	ofd->FilterIndex = 2;
	//タイトルを設定する
	ofd->Title = "開くファイルを選択してください";

	//ダイアログを表示する
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		//OKボタンがクリックされたとき、選択されたファイル名を表示する
		//MessageBox::Show(ofd->FileName);
		if (index == 1) {
			textBox1->Text = ofd->FileName;
		}
		else if (index == 2) {
			textBox2->Text = ofd->FileName;
		}
	}
	return System::Void();
}

String ^ TestProject::MyForm::getDeleteExtension(String ^ str)
{
	String^ res = str;
	cli::array<String^>^ tmpArray = res->Split('.');
	String^ ext = tmpArray[tmpArray->Length - 1];
	res = res->Replace("."+ext, "");
	return res;
}

String ^ TestProject::MyForm::getDeleteTail(String ^ str)
{
	String^ res = str;
	cli::array<String^>^ tmpArray = res->Split('_');
	String^ tail = tmpArray[tmpArray->Length - 1];
	res = res->Replace("_" + tail, "");
	
	return res;
}

System::Void TestProject::MyForm::button3_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	openFileDialog(2);
	return System::Void();
}


