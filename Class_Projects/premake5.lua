outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

------------------------------------------------------------------
------------------------------------------------------------------

workspace "Class_Projects"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    platforms
    {
        "Windows"
    }

------------------------------------------------------------------
------------------------------------------------------------------

project "P-04-05-12_Dates"
    location "P-04-05-12_Dates"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-06_RockPaperScissors"
    location "P-06_RockPaperScissors"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-09_LinkedList"
    location "P-09_LinkedList"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-16-25_TicTacToe"
    location "P-16-25_TicTacToe"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-17-18_ASCII"
    location "P-17-18_ASCII"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-08-19_Animations"
    location "P-08-19_Animations"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-22-23-24_Student"
    location "P-22-23-24_Student"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-26_XCommonWord"
    location "P-26_XCommonWord"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-28_2sComplement"
    location "P-28_2sComplement"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-10-13_LexicographicOrder"
    location "P-10-13_LexicographicOrder"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-20_Eratosthenes"
    location "P-20_Eratosthenes"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-21_NRankDeterminant"
    location "P-21_NRankDeterminant"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-07_FileExplorer"
    location "P-07_FileExplorer"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-03_ClockAngle"
    location "P-03_ClockAngle"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-11_Knapsack"
    location "P-11_Knapsack"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-01-02_Huffman"
    location "P-01-02_Huffman"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-14-15_LZW"
    location "P-14-15_LZW"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-29_Bases"
    location "P-29_Bases"
    dofile("CommonProjectSettings.lua")

------------------------------------------------------------------
------------------------------------------------------------------

project "P-27_Questionaree"
location "P-27_Questionaree"
dofile("CommonProjectSettings.lua")