#pragma once


#include "DateConvertor.h"

namespace development
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace aofz;

	/// <summary> 
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the 
	///          'Resource File Name' property for the managed resource compiler tool 
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public __gc class Form1 : public System::Windows::Forms::Form
	{
	public: String * path;
	public: String * msgTitle;
	public: String * errGui;
	private: System::Windows::Forms::Timer *  tmr_date;
	private: AxInterop::ShockwaveFlashObjects::AxShockwaveFlash *  guiFlash;


	public: String * errDb;
	public:
		Form1(void)
		{
			InitializeComponent();

			path = String::Concat(Directory::GetCurrentDirectory(), Path::DirectorySeparatorChar.ToString());
			msgTitle = "ÊæÓÚå ÇáßÊÑæäíß ÝÑÏÇ - ÎØÇí ÒãÇä ÇÌÑÇ";
			errGui = "ÇãßÇä ÏÓÊÑÓí Èå ÑÇÈØ ÑÇÝíßí ßÇÑÈÑ æÌæÏ äÏÇÑÏ";
			errDb = "ÇãßÇä ÏÓÊÑÓí Èå ÇíÇå ÏÇÏå æÌæÏ äÏÇÑÏ";

			bool found = ChkFiles("gui.swf", errGui);
			found &= ChkFiles("development.mdb", errDb);
			if (!found)
			{
				Environment::Exit(Environment::ExitCode);
			}

			guiFlash->Width = Screen::PrimaryScreen->Bounds.Width;
			guiFlash->Height = Screen::PrimaryScreen->Bounds.Height;
			guiFlash->SetVariable("_quality", "BEST");
			guiFlash->LoadMovie(0, String::Concat(path, S"gui.swf"));
		}
  
	protected:
		void Dispose(Boolean disposing)
		{
			if (disposing && components)
			{
				components->Dispose();
			}
			__super::Dispose(disposing);
		}

	private: System::ComponentModel::IContainer *  components;




	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = new System::ComponentModel::Container();
			System::Resources::ResourceManager *  resources = new System::Resources::ResourceManager(__typeof(development::Form1));
			this->tmr_date = new System::Windows::Forms::Timer(this->components);
			this->guiFlash = new AxInterop::ShockwaveFlashObjects::AxShockwaveFlash();
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->guiFlash))->BeginInit();
			this->SuspendLayout();
			// 
			// tmr_date
			// 
			this->tmr_date->Enabled = true;
			this->tmr_date->Interval = 999;
			this->tmr_date->Tick += new System::EventHandler(this, tmr_date_Tick);
			// 
			// guiFlash
			// 
			this->guiFlash->Enabled = true;
			this->guiFlash->Location = System::Drawing::Point(0, 0);
			this->guiFlash->Name = S"guiFlash";
			this->guiFlash->OcxState = (__try_cast<System::Windows::Forms::AxHost::State *  >(resources->GetObject(S"guiFlash.OcxState")));
			this->guiFlash->Size = System::Drawing::Size(1152, 864);
			this->guiFlash->TabIndex = 0;
			// 
			// Form1
			// 
			this->AutoScaleBaseSize = System::Drawing::Size(7, 19);
			this->ClientSize = System::Drawing::Size(1152, 864);
			this->ControlBox = false;
			this->Controls->Add(this->guiFlash);
			this->Font = new System::Drawing::Font(S"Tahoma", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, (System::Byte)178);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = S"Form1";
			this->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->ShowInTaskbar = false;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->TopMost = true;
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->Load += new System::EventHandler(this, Form1_Load);
			(__try_cast<System::ComponentModel::ISupportInitialize *  >(this->guiFlash))->EndInit();
			this->ResumeLayout(false);

		}	

	private:
		bool ChkFiles(String * fileName, String * errMsg)
		{
			String * file = String::Concat(path, fileName);
			bool found = File::Exists(file);
			if (!found)
			{
				MessageBox::Show(String::Concat(errMsg, S"\n\nDetails:\n", file, "\t...Not Found"), msgTitle, MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
			return found;
		}
	private:
		String * CallToFlash(String * request, String * args)
		{
			try
			{
				return guiFlash->CallFunction(String::Format(S"<invoke name=\"{0}\"><arguments><string>{1}</string></arguments></invoke>", request, args));
			}
			catch(System::Exception * e)
			{
				return e->ToString();
			}
		}
	private:
		System::Void Form1_Load(System::Object *  sender, System::EventArgs *  e)
		{
			String * result = CallToFlash(S"BootUp", String::Empty);
			if (String::Compare(result, S"<string>success</string>"))
			{
				MessageBox::Show(String::Concat(errGui, S"\n\nDetails:\n", result), msgTitle, MessageBoxButtons::OK, MessageBoxIcon::Error);
				Application::Exit();
			}
		}

	private:
		System::Void tmr_date_Tick(System::Object *  sender, System::EventArgs *  e)
		{
			guiFlash->SetVariable("_root.dateShamsi", DateConvertor::GeorgianToShamsi());
			guiFlash->SetVariable("_root.dateGeorgian", String::Format("{0}/{1}/{2}", DateTime::Now.Year.ToString(), DateTime::Now.Month.ToString(), DateTime::Now.Day.ToString()));
		}

};
}