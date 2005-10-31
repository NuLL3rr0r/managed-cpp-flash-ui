#pragma once


namespace aofz
{

	public __gc class DateConvertor
	{

	public:
		static System::String * About()
		{
			return S"Written By: \n\tMohammad Sadegh Babaei;\n\nmailto:\n\tace.of.zerosync@gmail.com";
		}


	private:
		static System::String * CheckRange(unsigned __int16 year, unsigned __int8 month, unsigned __int8 day)
		{
			unsigned __int8 months[12] = {31, !System::DateTime::IsLeapYear( year ) ? 28 : 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
			for (unsigned __int8 index = 0; index < 12; index++)
				if ((month == index + 1) || (month == 0))
				{
                    System::String * msgError = ((year < 10000) && (year > 0)) ? S" " : S"err *0:\tYear range is not validate;\n\t\tPlease enter a num between [1-9999]...";
					msgError = System::String::Concat(msgError->Trim(), ((month < 13) && (month > 0)) ? S" " : System::String::Concat((msgError->Trim() == System::String::Empty) ? S" " : S"\n\n", S"err *1:\tMonth range is not validate;\n\t\tPlease enter a num between [1-12]..."));
					msgError = System::String::Concat(msgError->Trim(), ((day <= months[index]) && (day > 0)) ? S" " : System::String::Concat((msgError->Trim() == System::String::Empty) ? S" " : S"\n\n", S"err *2:\tDay range is not validate;\n\t\tPlease enter a num between [1-", System::Convert::ToString(months[index]), S"]..."));
					return msgError->Trim();
				}
		}


	private:
		static System::String * Calculate(unsigned __int16 georgianYear, unsigned __int8 georgianMonth, unsigned __int8 georgianDay, unsigned __int16 dayOfYear)
		{
			bool isLeapYear = System::DateTime::IsLeapYear(georgianYear - 1);

			System::String * persianYear = (georgianYear - 621).ToString();
			System::String * persianMonth;
			System::String * persianDay;

			unsigned __int16 dayMatch[13] = {80, 111, 142, 173, 204, 235, 266, 296, 326, 356, !isLeapYear ? 21 :20, !isLeapYear ? 51 : 50, 999};

			for (unsigned __int8 index = 0; index < 12; index++)
				if ((dayOfYear >= dayMatch[index] && dayOfYear < dayMatch[index+1]) || ((dayOfYear >= dayMatch[index] || dayOfYear < dayMatch[index+1]) && (index == 9)))
				{
					persianMonth = (index + 1).ToString();
					if (dayOfYear >= dayMatch[index])
						persianDay = (dayOfYear - dayMatch[index] + 1).ToString();
					else
					{
						if (!isLeapYear)
							persianDay = (dayOfYear + 10).ToString();
						else
							persianDay = (dayOfYear + 11).ToString();
					}
					break;
				}

			if (persianMonth->Length == 1)
				persianMonth = System::String::Concat(S"0", persianMonth);
			if (persianDay->Length == 1)
				persianDay = System::String::Concat(S"0", persianDay);

			return System::String::Concat(persianYear, S"/", persianMonth, S"/", persianDay);
		}


	public:
		static System::String * GeorgianToShamsi()
		{
			System::DateTime dt = System::DateTime::Now;
			return Calculate(dt.Year, dt.Month, dt.Day, dt.DayOfYear);
		}


	public:
		static System::String * GeorgianToShamsi(unsigned __int16 georgianYear, unsigned __int8 georgianMonth, unsigned __int8 georgianDay)
		{
			System::String * errGenerated = CheckRange(georgianYear, georgianMonth, georgianDay);
			if (errGenerated != System::String::Empty)
				return errGenerated;

			System::DateTime dt = System::DateTime(georgianYear, georgianMonth, georgianDay);

			return Calculate(georgianYear, georgianMonth, georgianDay, dt.DayOfYear);
		}

	};

}