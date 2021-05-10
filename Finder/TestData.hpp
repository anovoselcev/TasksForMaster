#pragma once
#include <finder.hpp>
#include <Duration.hpp>
#include <iostream>
#include <fstream>
#include <sstream>



void TestNull(){
    std::string data;
    std::string pattern;
    auto res = [data, pattern](){
        master::Duration("First null");
        return master::find(data, pattern);
    }();

    if(res){
        std::cout << "Wrong test#1 in nullptr test" << std::endl;
        return;
    }

    data = "From its very beginnings the Internet\0";
    pattern = "Hey!!!\0";

    res = [data, pattern](){
        master::Duration d("Second Null");
        return master::find(data, pattern);
    }();
    if(res){
        std::cout << "Wrong test#2 in nullptr test" << std::endl;
        return;
    }
    std::cout << "Test nullptr done" << std::endl;
}

void TestLittleArticle(){
    std::string data = "From its very beginnings the Internet"
                       "became a crucial part of each and any"
                       " infrastructure. Similar to the discoveries"
                       " of electricity, microorganisms or elementary"
                       " particles, the creation of the Internet has"
                       " turned a new page in the history of humanity."
                       "The history of the Internet has begun in the"
                       " middle of the 20th century as a result of"
                       " rapid development of computer science."
                       " Computers of that age were still relatively"
                       " underperforming and needed constant maintenance."
                       " Some kind of an effective and automated method"
                       " of time-sharing between users needed to be devised"
                       " and implemented for them to work reliably.";

    std::string pattern = " implemented for them";

    auto res = [data, pattern](){
        master::Duration d("Article");
        return master::find(data, pattern);
    }();

    if(!res){
        std::cout << "TestLittleArticle - nullptr" << std::endl;
        return;
    }
    std::cout << "TestLittleArticle - " << (pattern == data.substr(res.value(), pattern.size())) << std::endl;
}

void TestBook(){
    std::string data = "This will never happen. Not even humans,"
                       " with all their intuition and creativity,"
                       " have been able to create successful systems"
                       " from the vague feelings of their customers."
                       " Indeed, if the discipline of requirements"
                       " specification has taught us anything, it is"
                       " that well-specified requirements are as formal"
                       " as code and can act as executable tests of that"
                       " code! Remember that code is really the language"
                       " in which we ultimately express the requirements."
                       " We may create languages that are closer to the"
                       " requirements. We may create tools that help us"
                       " parse and assemble those requirements into formal"
                       " structures. But we will never eliminate necessary"
                       " precision—so there will always be code. Bad Code I"
                       " was recently reading the preface to Kent Beck’s"
                       " book Implementation Patterns.1 He says, “… this book"
                       " is based on a rather fragile premise: that good"
                       " code matters….” A fragile premise? I disagree!"
                       " I think that premise is one of the most robust,"
                       " supported, and overloaded of all the premises"
                       " in our craft (and I think Kent knows it). We"
                       " know good code matters because we’ve had to"
                       " deal for so long with its lack. I know of one"
                       " company that, in the late 80s, wrote a killer"
                       " app. It was very popular, and lots of professionals"
                       " bought and used it. But then the release cycles"
                       " began to stretch. Bugs were not repaired from one"
                       " release to the next. Load times grew and crashes "
                       "increased. I remember the day I shut the product"
                       " down in frustration and never used it again. The"
                       " company went out of business a short time after that.";


    std::string pattern = "a short time after that";


    auto res = [data, pattern](){
        master::Duration d("Book");
        return master::find(data, pattern);
    }();

    if(!res){
        std::cout << "TestBook - nullptr" << std::endl;
        return;
    }
    std::cout << "TestBook - " << (pattern == data.substr(res.value(), pattern.size())) << std::endl;

}

void TestDracula(){
    std::ifstream f;

    const char* data = "stoker_dracula_txt.txt\0";
    std::stringstream ss;
    std::ifstream patfile("big_pattern.txt");
    while(!patfile.eof()){
        std::string tmp;
        std::getline(patfile, tmp);
        ss << tmp << '\n';
    }
    patfile.close();
    std::string pattern = ss.str();
    //    std::string pattern =
    //                          "\"In manus tuas, Domine!\"he said, crossing himself as he\n"
    //                          "passed over the threshold. We closed the door behind us, lest\n"
    //                          "when we should have lit our lamps we should possibly attract\n"
    //                          "attention from the road. The Professor carefully tried the\n"
    //                          "lock, lest we might not be able to open it from within\n"
    //                          "should we be in a hurry making our exit. Then we all lit our\n"
    //                          "lamps and proceeded on our search.";
    //const char* pattern = "over\0";

    std::optional<size_t> res =  [data, &pattern](){
        master::Duration d("Dracula");
        return master::find_in_file(data, pattern);
    }();
    if(!res){
        std::cout << "Dracula - nullptr" << std::endl;
        return;
    }
    size_t size = pattern.size();
    std::string str;
    str.resize(size);
    f.open("stoker_dracula_txt.txt");
    f.seekg(res.value());
    f.read(&str.front(), size);
    std::cout << "Dracula - " << (str == pattern) << std::endl;
    f.close();

}


