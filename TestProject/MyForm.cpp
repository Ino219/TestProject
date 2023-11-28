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

		//�f�B���N�g�����̎擾
		String^ DirName = System::IO::Path::GetDirectoryName(fullPath);
		cli::array<String^>^ allFile = Directory::GetFiles(DirName);
		List<String^>^ arr = gcnew List<String^>;

		for (int i = 0; i < allFile->Length; i++) {
			//�t�@�C�����擾
			String^ fileName = allFile[i];
			String^ f_Dext = getDeleteExtension(fileName);
			String^ f_Dtail = getDeleteTail(f_Dext);
			//������t�@�C�����̎擾
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

	//�͂��߂̃t�@�C�������w�肷��
	//�͂��߂Ɂu�t�@�C�����v�ŕ\������镶������w�肷��
	ofd->FileName = "default.html";
	//�͂��߂ɕ\�������t�H���_���w�肷��
	//�w�肵�Ȃ��i��̕�����j�̎��́A���݂̃f�B���N�g�����\�������
	ofd->InitialDirectory = "C:\\Users\\chach\\Desktop\\ffolder";
	//[�t�@�C���̎��]�ɕ\�������I�������w�肷��
	//�w�肵�Ȃ��Ƃ��ׂẴt�@�C�����\�������
	ofd->Filter = "HTML�t�@�C��(*.html;*.htm)|*.html;*.htm|���ׂẴt�@�C��(*.*)|*.*";
	//[�t�@�C���̎��]�ł͂��߂ɑI���������̂��w�肷��
	//2�Ԗڂ́u���ׂẴt�@�C���v���I������Ă���悤�ɂ���
	ofd->FilterIndex = 2;
	//�^�C�g����ݒ肷��
	ofd->Title = "�J���t�@�C����I�����Ă�������";

	//�_�C�A���O��\������
	if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		//OK�{�^�����N���b�N���ꂽ�Ƃ��A�I�����ꂽ�t�@�C������\������
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


