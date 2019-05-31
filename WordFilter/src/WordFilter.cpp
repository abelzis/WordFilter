// WordFilter.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "wordfilter.h"

int main()
{
	ifstream inp;// ("text1.in");
	inp.open("text1.in");
	if (!inp.is_open())// || inp.fail())
	{
		std::cout << "No item is opened. Do you want to open a file? (Y): ";
		string ans;
		std::cin >> ans;
		bool answered = false;
		if (ans == "y" || ans == "ye" || ans == "yes" || ans == "yez")
		{
			std::cout << "\Please enter full file name with extension: ";
			string file_name;
			std::cin >> file_name;
			inp.open(file_name);
			if (inp.is_open())
				answered = true;
			if (!answered)
			{
				std::cout << "No file found. Exiting program.\n";
				return 0;
			}
		}

		if (answered == false)
		{
			std::cout << "\nDo you want to create one ? (Y) : ";
			std::cin >> ans;
			std::transform(ans.begin(), ans.end(), ans.begin(), ::tolower);
			if (ans == "y" || ans == "ye" || ans == "yes" || ans == "yez")
			{
				string default_text = "She exposed painted fifteen are noisier mistake led waiting. Surprise not wandered speedily husbands although yet end. Are court tiled cease young built fat one man taken. We highest ye friends is exposed equally in. Ignorant had too strictly followed. Astonished as travelling assistance or unreserved oh pianoforte ye. Five with seen put need tore add neat. Bringing it is he returned received raptures. Effects present letters inquiry no an removed or friends.Desire behind latter me though in.Supposing shameless am he engrossed up additions.My possible peculiar together to.Desire so better am cannot he up before points.Remember mistaken opinions it pleasure of debating.Court front maids forty if aware their at.Chicken use are pressed removed.";
				while (!inp.is_open())
				{
					string file_name;
					std::cout << "\nPlease enter full file name: ";
					std::cin >> file_name;
					ofstream temp(file_name);
					temp << default_text;
					temp.close();
					inp.open(file_name);
					if (!inp.is_open())
						std::cout << "\nError: wrong file name.\n";
				}
				std::cout << "\nFile successfully created and opened!\n";
			}
			else
			{
				std::cout << "\nExiting.";
				return 0;
			}
		}
	}
	Text t;
	t.readFromFile(inp);

	t.countWords();
	t.sortByCount();
	ofstream res("results.out");
	
	std::cout << "\nDo you want to sort by count? (Y) Else - alphabetically by first letter: ";
	string sorting;
	std::cin >> sorting;
	std::transform(sorting.begin(), sorting.end(), sorting.begin(), ::tolower);
	if (sorting == "y" || sorting == "ye" || sorting == "yes" || sorting == "yez")
		t.printWordsSortedByCount(res);
	else
		t.printWords(res);

	ofstream resURLs("url_results.out");
	t.printURLs(resURLs);
}
