// https://vjudge.net/user/memset0
#include<bits/stdc++.h>
using namespace std;
using T = pair<int, vector<int>>;
T M[]={
{30000,{0,21,1,52,1,5,1,57,1,47,1,72,1,4,1,81,1,5,1,66,1,50,1,27,1,27,1,23,1,5,1,17,1,9,1,151,1,68,1,64,1,33,1,46,1,48,1,36,1,50,1,11,1,29,1,48,1,15,1,58,1,49,1,27,1,96,1,37,1,14,1,7,1,97,1,19,1,68,1,51,1,20,1,40,1,155,1,30,1,49,1,25,1,49,1,11,1,4,1,68,1,7,1,53,1,58,1,100,1,1,1,23,1,94,1,79,1,16,1,65,1,100,1,184,1,55,1,130,1,5,1,51,1,6,1,163,1,176,1,1,1,75,1,81,1,30,1,36,1,17,1,45,1,5,2,29,1,184,1,10,1,51,1,48,1,99,1,34,1,147,1,113,1,72,1,75,1,55,1,132,1,34,1,101,1,86,1,174,1,79,1,31,1,48,1,61,1,89,1,326,1,38,1,9,1,79,1,44,1,34,1,115,1,52,1,64,1,37,1,23,1,139,1,131,1,88,1,15,1,166,2,73,1,3,1,7,1,60,1,34,1,162,1,6,1,8,1,42,1,22,1,20,1,44,1,52,1,73,1,22,1,172,1,28,1,53,1,31,1,62,1,101,1,123,1,214,1,83,1,97,1,108,1,6,1,86,1,85,1,49,1,51,1,131,1,37,1,64,1,1,1,232,1,132,1,142,1,105,1,22,1,60,1,47,1,23,1,29,1,107,1,17,1,82,1,71,1,34,1,67,1,7,1,3,1,63,1,34,1,12,1,2,1,76,1,54,1,51,1,127,1,101,1,39,1,56,1,23,1,125,1,35,1,30,1,27,1,8,1,105,1,65,1,98,1,79,1,40,1,42,1,7,1,5,1,135,1,6,1,23,1,12,1,58,1,171,1,120,2,37,1,86,1,91,1,1,1,18,1,12,1,76,1,283,1,37,1,105,1,250,1,50,1,38,1,276,1,137,1,7,1,96,1,9,1,7,1,48,1,65,1,56,1,47,1,148,1,41,1,61,1,64,2,31,1,16,1,53,1,130,1,40,1,40,1,1,1,35,1,93,1,100,1,121,1,137,2,154,1,53,1,41,1,40,1,83,1,36,1,188,1,98,1,10,1,67,1,130,1,54,1,281,1,105,1,35,1,3,1,70,1,99,1,63,1,33,1,68,1,10,1,97,1,28,1,41,1,38,1,182,1,16,1,19,1,57,1,52,1,56,1,65,1,15,1,67,1,8,1,31,1,180,1,6,1,20,1,8,1,39,1,270,1,8,1,5,1,67,1,133,1,151,1,66,1,66,1,38,1,3,1,152,1,105,1,9,1,55,1,32,1,105,1,174,1,59,1,346,1,11,1,56,1,185,1,9,2,20,1,48,1,94,1,12,1,26,1,11,1,216,1,5,1,244,1,126,1,30,1,112,1,28,1,160,1,102,1,171,1,11,1,33,1,77,1,29,1,135,1,62,1,130,1,136,1,15,1,6,1,207,1,19,1,50,1,23,2,6,1,72,1,28,1,64,1,96,1,31,1,9,1,17,1,181,1,13,1,51,1,53,1,12,1,3,1,12,1,54,1,144,1,195,1,2,1,29,1,94,1,34,1,41,1,65,1,36,1,3,1,2,1,36,1,34,1,1,1,15,1,1,1,18,1,52,1,74,1,10,1,62,1,215,1,65,1,170,1,69,1,6,1,17,1,35,1,21,1,7,1,101,1,39,1,44,1,150,1,3,1,104,1,124,1,81,1,125,1,69,1,14,1,33,1,189,1,44,1,76,1,127,1,127,1,20,1,84,1,3,1,44,1,32,1,84,1,93,1,22,1,57,1,46,1,172,1,47,1,139,1,5,1,118,1,30,1,119,1,15,1,39,1,132,1,12,1,38,1,25,1,63,1,104,1,57,1,18,1,8,1,140,1,140,1,15,1,187,1,45,1,67,1,68,1,69,1,39,1,150,1,30,1,17,1,118,1,102,1,162,1,56,1,118,1,67,1,58,1,4,1,136,1,32,1,52,1,19,1,69,1,200,1,58,1,11,1,24,1,5,1,117,1,13,1,408,1,30,1,98,1,106,1,25,1,14,1,6,1,19,1,9,1,33,1,20,1,41,1,62,1,66,1,164,1,4,1,28,1,2,1,23,1,2,1,24,1,2,1,2,1,10,1,81,1,29,1,22,1,20,1,65,1,187,1,19,1,55,1,49,1,12,1,52,1,108,1,95,1,33,1,22,1,3,1,177,1,35,1,61,1,19,1,82,1,110,1,184,1,60,1,23,1,90,1,35,1,20,1,6,1,119,1,274,1,74,1,7,1,30,1,46,1,94,1,23,1,62,1,55,1,3,1,68,1,32,1,111,1,14,1,3,1,29,1,242,1,194,1,26,1,8,1,61,1,40,1,37,1,18,1,37,1,28,1,61,1,11,1,112,1,9,1,107,1,33,1,2,1,32,1,107,1,57,1,50,1,1,1,19,1,18,1,8,1,28,1,72,1,237,1,33,1,72,1,67,1,40,1,86,1,113,1,38,1,34,1,52,1,12,1,63,1,115,1,11,1,109,1,54,1,64,1,1,1,127,1,10,1,55,1,47,1,59,1,3,1,4,1,28,1,75,1,86,1,32,1,26,1,10,1,22,1,25,1,88,1,33,1,37,1,28,1,16,1,78,1,9,1,20,1,9,1,61,1,2,1,74,1,34,1,19,1,46,1,317,1,232,1,153,1,125,1,15,1,31,1,60,1,31,1,29,1,6,1,35,1,93,1,4,1,5,1,22,1,34,1,47,1,60,1,39,1,179,1,9,1,53,1,183,1,42,1,4,1,89,1,17,1,176,1,38,1,1,1,3,1,14,1,160,1,9,1,96,1,10,1,232,1,50,1,69,1,21,1,104,1,20,1,178,1,34,1,59,1,3,1,7,1,56,1,50,1,85,1,23,1,20,1,332,1,46,1,19,1,40,1,23,1,72,1,18,1,95,1,4,1,350,1,46,1,3,1,186,1,55,1,32,1,19,1,42,1,104,1,209,1,10,1,29,1,113,1,81,1,59,1,28,1,155,1,7,1,80,1,9,1,8,1,32,1,97,1,3,1,92,1,4,1,5,1,59,1,19,1,1,1,296,1,68,1,117,1,169,1,39,1,157,1,51,1,50,1,41,1,22,1,29,1,4,1,17,1,39,1,63,1,35,1,23,1,9,1,8,1,6,1,171,1,26,1,16,1,11,1,20,1,57,1,41,1,1,1,51,1,112,1,105,1,3,1,91,1,127,1,9,1,5,1,61,1,89,1,116,1,10,1,41,1,42,1,164,1,10,1,41,1,33,1,62,1,17,1,59,1,22,1,90,1,25,1,97,1,2,1,62,1,95,1,35,1,2,1,46,1,106,1,27,1,125,1,121,1,90,1,52,1,9,1,47,1,304,1,79,1,21,1,101,1,44,1,84,1,37,1,10,1,19,1,9,1,58,1,37,1,26,1,35,1,13,1,61,1,43,1,54,1,31,1,7,2,111,1,119,1,231,1,14}},
{100000,{0,61,1,162,1,68,1,37,1,51,1,302,1,59,1,132,1,43,1,397,1,226,1,37,1,47,1,200,1,266,1,30,1,170,1,135,1,90,1,315,1,51,1,48,1,158,1,41,1,131,1,596,1,344,1,28,1,88,1,129,1,121,1,327,1,380,1,58,1,208,1,96,1,71,1,155,1,63,1,84,1,102,1,45,1,175,1,605,1,146,1,141,1,25,1,47,1,169,1,168,1,37,1,10,1,14,1,43,1,245,1,311,1,105,1,7,1,94,1,61,1,49,1,345,1,6,1,237,1,231,1,39,1,260,1,60,1,125,1,33,1,47,1,161,1,162,1,147,1,10,1,8,1,129,1,685,1,159,1,31,1,120,1,129,1,406,1,73,1,69,1,147,1,214,1,17,1,128,1,229,1,66,1,6,1,97,1,374,1,681,1,73,1,63,1,157,1,27,1,63,1,256,1,50,1,79,1,184,1,11,1,229,1,14,1,23,1,95,1,140,1,231,1,39,1,129,1,52,1,37,1,134,1,89,1,19,1,402,1,13,1,273,1,162,1,9,1,97,1,181,1,27,1,224,1,528,1,120,1,61,1,70,1,115,1,112,1,250,1,314,1,732,1,170,1,18,1,106,1,143,1,47,1,157,1,58,1,209,1,273,1,125,1,19,1,56,1,245,1,7,1,8,1,110,1,123,1,587,1,286,1,46,1,313,1,37,1,57,1,369,1,7,1,29,1,182,1,95,1,72,1,272,1,67,1,3,1,301,1,256,1,21,1,135,1,59,1,154,1,76,1,173,1,345,1,181,1,461,1,95,1,119,1,21,1,24,1,41,1,183,1,36,1,17,1,41,1,99,1,80,1,25,1,92,1,195,2,17,1,48,1,38,1,67,1,140,1,343,1,115,1,50,1,96,1,124,1,107,1,71,1,117,1,62,1,69,1,184,1,386,1,121,1,131,1,16,1,246,1,15,1,265,1,41,1,368,1,89,1,666,1,53,1,143,1,545,1,324,1,175,1,16,1,102,1,28,1,55,1,100,1,430,1,269,1,459,1,139,1,188,1,24,1,40,1,26,1,293,1,493,1,200,1,421,1,63,1,105,1,75,1,23,1,422,1,21,1,133,1,12,1,105,1,183,1,453,1,12,1,96,1,50,1,2,1,338,1,175,1,484,1,259,1,173,1,15,1,307,1,171,1,34,1,21,1,38,1,825,1,102,1,45,1,210,1,162,1,189,1,14,1,37,1,135,1,76,1,548,1,32,1,856,1,356,1,66,1,219,1,167,1,32,1,65,1,222,1,23,1,146,1,82,1,222,1,140,1,58,1,56,1,352,1,329,1,537,1,307,1,71,1,491,1,145,1,4,1,307,1,148,1,13,1,57,1,55,1,548,1,280,1,56,1,54,1,48,1,213,1,195,1,14,1,86,1,56,1,216,1,214,1,282,1,501,1,119,1,242,1,104,1,260,1,415,1,102,1,70,1,31,1,160,1,327,1,62,1,155,1,394,1,203,1,29,1,97,1,22,1,137,1,3,1,39,1,303,1,199,1,151,1,379,1,272,1,2,1,97,1,32,1,70,1,130,1,101,1,19,1,56,1,201,1,105,1,277,1,107,1,202,1,57,1,58,1,52,1,161,1,635,1,65,1,240,1,70,1,332,1,47,1,107,1,56,1,105,1,192,1,42,1,24,1,235,1,36,1,113,1,128,1,169,1,17,1,172,1,68,1,106,1,76,1,186,1,109,1,147,1,233,1,16,1,602,1,125,1,131,1,174,1,32,1,36,1,154,1,145,1,225,1,408,1,220,1,22,1,29,1,17,1,4,1,423,1,88,1,266,1,102,1,165,1,320,1,529,1,11,1,108,1,254,1,184,1,59,1,487,1,253,1,158,1,428,1,5,1,108,1,196,1,245,1,173,1,35,1,52,1,38,1,54,1,485,1,210,1,296,1,14,1,32,1,82,1,25,1,5,1,26,1,81,1,11,1,191,1,277,1,138,1,196,1,83,1,55,1,206,1,466,2,36,1,214,1,8,1,52,1,258,1,131,1,72,1,184,1,112,1,15,1,61,1,122,2,151,1,85,1,118,1,158,1,119,1,805,1,20,1,121,1,411,1,249,1,745,1,87,1,40,1,97,1,24,1,155,1,440,1,88,1,4,1,68,1,11,1,411,1,367,1,60,1,413,1,6,1,4,1,80,1,73,1,114,1,90,1,1,1,125,1,364,1,278,1,54,1,71,1,79,1,25,1,25,1,120,1,5,1,65,1,47,1,300,1,276,1,366,1,137,1,288,1,371,2,7,1,18,1,54,1,49,1,35,1,101,1,284,1,95,1,43,1,715,1,285,1,126,1,58,1,40,1,328,1,41,1,184,1,663,1,99,1,91,1,142,1,76,1,112,1,153,1,75,1,5,1,154,1,7,1,62,1,101,1,112,1,64,1,116,1,182,1,6,1,196,1,67,1,37,1,34,1,210,1,22,1,48,1,92,1,66,1,62,1,87,1,38,1,85,1,20,1,43,1,398,1,62,1,415,1,203,1,111,1,48,1,151,1,58,1,169,1,160,1,333,1,54,1,42,1,3,1,137,1,53,1,35,1,58,1,870,1,53,1,48,1,9,1,208,1,121,1,63,1,56,1,323,1,253,1,159,1,229,1,37,1,126,1,47,1,85,1,34,1,242,1,14,1,142,1,39,1,247,1,69,1,39,1,17,1,8,1,381,1,38,1,2,1,16,1,66,1,142,1,30,1,502,1,92,1,87,1,25,1,69,1,263,1,203,1,35,1,728,1,86,1,225,1,17,1,166,1,175,1,93,1,309,1,2,1,59,1,44,1,144,1,27,1,18,1,84,1,576,1,42,1,280,1,7,1,354,1,147,1,54,1,17,1,169,1,61,1,171,1,362,1,258,1,1,1,257,1,245,1,130,1,124}},
{7,{2,1,2}},
{100,{0,1,1,2,2,1,1,1,5,2,2,1,1,3,1,4,1,1,1,2,1,2,2,1,1,1,6,2,1,2,1,1,2,1,1,1,1,4,1,1,1,1,1,3,2,1,1,5,1,2,1,3,2,3,2,3,1,1}},
{100000,{0,5,1,337,1,19,1,109,1,46,1,49,1,635,1,87,1,54,1,377,1,122,1,10,1,37,1,32,1,26,1,3,1,26,1,121,1,17,1,27,1,33,1,48,1,21,1,58,1,376,1,98,1,171,1,99,1,184,1,11,1,425,1,140,1,131,1,38,1,50,1,24,1,55,1,148,1,75,1,123,1,105,1,187,1,36,1,141,1,84,1,30,1,147,1,119,1,500,1,29,1,153,1,5,1,28,1,28,1,49,1,274,1,26,1,14,1,55,1,139,1,4,1,26,1,59,1,38,1,62,1,259,1,74,1,99,1,1,1,238,1,194,1,83,1,6,1,128,1,14,1,122,1,99,1,106,1,165,1,180,1,51,1,58,1,5,1,44,1,94,1,41,1,20,1,28,1,19,1,120,1,256,1,31,1,1,1,94,1,118,1,160,1,35,1,81,1,23,1,233,1,61,1,35,1,65,1,31,1,27,1,46,1,20,1,67,1,97,1,100,1,26,1,30,1,141,1,34,1,10,1,2,1,132,1,39,1,11,1,5,1,194,1,105,1,334,1,167,1,122,1,70,1,65,1,5,1,98,1,49,1,18,1,161,1,147,1,70,1,82,1,91,1,1,1,145,1,67,1,2,1,50,1,40,1,104,1,110,1,240,1,18,1,53,1,45,1,210,1,82,1,173,1,151,1,12,1,214,1,71,1,108,1,176,1,189,1,137,1,447,1,64,1,11,1,187,1,18,1,165,1,138,1,148,1,45,1,21,1,299,1,175,1,43,1,27,1,9,1,76,1,105,1,54,1,50,1,104,1,178,1,103,1,69,1,96,1,68,1,182,1,70,1,51,1,100,1,467,1,40,1,2,1,6,1,49,1,9,1,245,1,23,1,134,1,23,1,2,1,41,2,84,1,231,1,34,1,17,1,64,1,133,1,77,1,58,1,59,1,50,1,135,1,79,1,112,1,30,1,98,1,57,1,191,1,149,1,137,1,78,1,101,1,72,1,222,1,41,1,18,1,9,1,91,1,53,1,122,1,98,1,85,1,99,1,98,1,28,1,183,1,117,1,6,1,120,1,7,1,23,1,200,1,127,1,17,1,61,1,106,1,7,1,115,1,49,1,258,1,26,1,2,1,115,2,5,1,136,1,16,1,44,1,516,1,297,1,9,1,9,1,17,1,90,1,96,1,106,1,78,1,19,1,32,1,33,1,2,1,2,1,438,1,88,1,2,1,39,1,25,1,105,1,15,1,274,1,133,1,96,1,46,1,51,1,104,1,152,1,132,1,136,1,96,1,52,1,59,1,142,1,208,1,58,1,43,1,238,1,40,1,13,1,164,1,193,1,12,1,49,1,126,1,17,1,194,1,22,1,9,1,132,1,34,1,124,1,12,1,35,1,79,1,117,1,4,1,28,1,118,1,59,1,97,1,118,1,33,1,35,1,159,1,63,1,193,1,530,1,157,1,73,1,308,1,104,1,156,1,243,2,206,1,88,1,39,1,22,1,2,1,63,1,45,1,56,1,17,1,41,1,143,1,18,1,69,1,41,1,61,1,102,1,234,1,18,1,2,1,134,1,63,2,333,1,91,1,136,1,61,1,60,1,109,1,7,1,255,1,53,1,21,1,40,1,211,1,258,1,128,1,73,1,69,1,7,1,281,1,178,1,209,1,62,1,62,1,87,1,77,1,210,1,296,1,18,1,87,1,58,1,80,1,102,1,15,1,41,1,77,1,38,1,47,1,88,1,14,1,10,1,191,1,276,1,6,1,33,1,95,1,54,1,114,1,13,1,76,1,348,1,46,1,237,1,34,1,9,1,4,1,46,1,379,1,36,2,195,2,182,1,199,1,95,1,85,1,183,1,247,1,26,1,109,1,67,1,3,1,247,1,25,1,26,1,53,1,63,1,16,1,105,1,116,1,89,1,6,1,283,1,73,1,56,1,9,1,34,1,18,1,70,1,168,1,299,1,25,1,88,1,60,1,16,1,8,1,21,1,102,1,14,1,174,1,51,1,57,1,31,1,6,1,120,1,122,1,148,1,92,1,8,1,168,1,62,1,43,1,17,1,38,1,11,1,60,1,5,1,55,1,117,1,10,1,55,1,67,1,25,1,468,1,159,1,60,1,634,1,59,1,4,1,137,1,119,1,15,1,160,1,49,1,104,1,26,1,65,1,424,1,96,1,52,1,164,1,46,1,168,1,97,1,108,1,95,1,38,1,26,1,288,1,283,1,160,1,64,1,41,1,123,1,32,1,93,1,12,1,327,1,83,1,41,1,59,1,61,1,77,1,1,1,115,1,15,1,7,1,3,1,349,1,33,1,4,1,10,1,219,1,400,1,40,1,52,1,70,1,101,1,134,1,236,1,1,1,90,1,121,1,53,1,36,1,6,1,100,1,65,1,119,1,39,1,60,1,200,1,488,1,53,1,66,1,17,1,160,1,48,1,86,1,148,1,1,1,25,1,146,1,103,1,78,1,146,1,138,1,180,1,293,1,26,1,90,1,18,1,190,1,7,1,157,1,68,1,234,1,46,1,101,1,169,1,244,1,1,1,45,1,140,1,159,1,62,1,132,1,24,1,202,1,54,1,61,1,52,1,130,1,28,1,19,1,58,1,13,1,125,1,172,1,69,1,15,1,32,1,46,1,43,1,14,1,57,1,126,1,295,1,145,1,185,1,131,1,161,1,1,1,59,1,2,1,218,1,154,1,30,1,42,1,92,1,117,1,116,1,87,1,62,1,38,1,15,1,339,1,109,1,80,1,55,1,40,1,11,1,11,1,25,1,113,1,166,1,105,1,10,1,89,1,185,1,144,1,73,1,36,1,310,1,132,1,169,1,36,1,178,1,5,1,17,1,36,1,93,1,237,1,83,1,176,1,77,1,68,1,200,1,26,1,4,1,10,1,110,1,232,1,15,1,258,1,15,1,59,1,134,1,511,1,85,1,4,1,30,1,32,1,60,1,99,1,22,1,8,1,294,1,94,1,145,1,29,1,54,1,117,1,152,1,104,1,127,1,189,1,54,1,1,1,3,1,5,1,135,1,266,1,85,1,221,1,130,1,174,1,306,1,64,1,11,1,131,1,67,1,14,1,58,1,320,1,40,1,10,1,27,1,2,1,38,1,12,1,27,1,54,1,33,1,178,1,102,1,152,1,106,1,267,1,164,1,164,1,41,1,29,1,196,1,151,1,66,1,238,1,76,1,95,1,4,1,6,1,62,1,201,1,114,1,119,1,107,1,104,1,247,1,228,1,180,1,92,1,102,1,424,1,128,1,47,1,12,1,147,1,15,1,132,1,31,1,60,1,32,1,230,1,12,1,20,1,70,1,82,1,66,1,292,1,34,1,409,1,37,1,52,1,31,1,100,1,185,1,28,1,54,1,22,1,194,1,79,1,265,1,24,1,207,1,70,1,31,1,46,1,46,1,314,1,53,1,190,1,205,1,88,1,145,1,115,1,53,1,87,1,64,1,52,1,275,1,37,1,24,1,56,1,158,1,228,1,195,1,51,1,43,1,18,1,205,1,128,1,146,1,27,1,56,1,110,1,48,1,60,1,364,1,426,1,99,1,23,1,143,1,97,1,58,1,5,1,18,1,25,1,210,1,8,1,39,1,169,1,3,1,158,1,275,1,50,1,53,1,58,1,253,1,99,1,18,1,233,1,19,1,199,1,1,1,44,1,68,1,173,1,95,1,43,1,28,1,68,1,128,1,47,1,222,1,46,1,7,1,38,1,5,1,114,1,234,1,114,1,71,1,52,1,35,1,81,1,167,1,61,1,102,1,54,1,95,1,207,1,12,1,97,1,85,1,343,1,26,1,47,1,139,1,73,1,49,1,19,1,276,1,36,1,181,1,2,1,60,1,4,1,132,1,170,1,67,1,54,1,22,1,6,1,5,1,105,1,131,1,46,1,51,1,8,1,19,1,27,1,36,1,376,1,43,1,109,1,286,1,17,1,151,1,166,1,214,1,90,1,150,1,9,1,147,1,17,1,3,1,18,1,5,1,115,1,242,2,17,1,20,1,115,1,77,1,339,1,237,1,18,1,207,1,89,1,70,1,53,1,25,1,245,1,90,1,4,2,9,1,35,1,28,1,238,2,148,1,79,1,64,1,23,1,13,1,143,1,8,1,46,1,43,1,45,1,55,1,4,1,79,1,3,1,52,1,58,1,110,1,58,1,36,1,382,1,304,1,182,1,25,1,108,1,73,1,105,1,161,1,38,1,46,1,65,1,167,1,36,1,24,1,17,1,20,1,47,1,85,1,9,1,39,1,97,1,185,1,107,1,203,1,69,1,73,1,136,1,82,1,71,1,58,1,54,1,238,1,35,1,124,1,16,1,70,1,53,1,154,1,31,1,43,1,68,1,480,1,50,1,7,1,86,1,25,1,153,1,12,1,64,1,65,1,396,1,87,1,75,1,7,1,230,1,23,1,45,1,194,1,95,1,59,1,186,1,55,1,154,1,491,1,29,1,115}},
{70000,{0,96,1,425,1,169,1,383,1,47,1,136,1,81,1,49,1,109,1,392,1,119,1,103,1,201,1,255,1,4,1,237,1,420,1,39,1,40,1,73,1,320,1,17,1,30,1,115,1,84,1,543,1,441,1,109,1,257,1,20,1,133,1,97,1,94,1,810,1,454,1,142,1,368,1,81,1,41,1,1175,1,67,1,133,1,124,1,219,1,35,1,237,1,128,1,218,1,60,1,27,1,72,1,2,1,101,1,145,1,145,1,288,1,227,1,193,1,218,1,82,1,23,1,43,1,110,1,28,1,444,1,244,1,127,1,216,1,230,1,250,1,161,1,206,1,509,1,170,1,171,1,420,1,211,1,122,1,775,1,7,1,138,1,21,1,205,1,169,1,219,1,271,1,254,1,336,1,268,1,84,1,323,1,299,1,324,1,274,1,220,1,440,1,39,1,180,1,107,1,244,1,403,1,302,1,32,1,194,1,199,1,119,1,182,1,321,1,760,1,155,1,78,1,114,1,115,1,119,1,32,1,227,1,77,1,683,1,353,1,88,1,586,1,181,1,745,1,55,1,112,1,141,1,129,1,570,1,59,1,444,1,45,1,316,1,956,1,297,1,198,1,193,1,177,1,948,1,28,1,8,1,16,1,16,1,857,1,636,1,208,1,19,1,105,1,346,1,77,1,186,1,87,1,775,1,47,1,34,1,112,1,256,1,246,1,109,1,251,1,46,1,23,1,15,1,40,1,161,1,147,1,107,1,179,1,11,1,114,1,81,1,2,1,217,1,77,1,83,1,339,1,22,1,814,1,276,1,167,1,356,1,583,1,187,1,676,1,34,1,327,1,576,1,432,1,23,1,131,1,577,1,254,1,157,1,358,1,147,1,45,1,99,1,320,1,124,1,178,1,163,1,5,1,319,1,714,1,143,1,61,1,172,1,1,1,171,1,47,1,40,1,234,1,704,1,57,1,59,1,15,1,54,1,132,1,56,1,548,1,195,1,114,1,32,1,458,1,2,1,291,1,293,1,65,1,284,1,583,1,60,1,113,1,214,1,15,1,74,1,114,1,49,1,34,1,512,1,85,1,66,1,42,1,204,1,104,1,102,1,41,1,49,2,97,1,714,1,73,1,480,1,305,1,781,1,211,1,26,1,84,1,78,1,603,1,97,1,178,1,68,1,275,1,468,1,190,1,169,1,18,1,544,1,572,1,44,1,917,1,410,1,776,1,177,1,276,1,404,1,219,1,20,1,53,1,42,1,200,1,355,1,77,1,65,1,7,1,9,1,42,1,6,1,84,1,411,1,412,1,193,1,51,1,22,1,31,1,281,1,10,1,68,1,131,1,92,1,64,1,152,1,227,1,172,1,190,1,229,1,1613,1,129,1,374,1,161,1,141,1,431,1,521,1,97,1,100,1,728,1,155,1,216,1,204,1,281,1,1,1,217,1,22,1,185,1,59,1,130,1,172,1,78,1,185,1,649,1,536,1,387,1,49,1,270,1,485,1,102,1,517,1,656,1,192,1,303,1,255,1,120,1,107,1,68,1,407,1,244,1,424,1,67,1,228,2,243,1,100,1,192,1,2,1,297,1,52,1,121,1,420,1,317,1,851}},
{12,{1,1,3}},
{5,{0,1,1,1}},
{4,{0,1,2,1,2}},
{8000,{0,13,1,17,1,10,1,57,1,16,1,62,1,19,1,6,1,6,1,6,1,18,1,35,1,14,1,13,1,21,1,4,1,27,1,12,1,12,1,18,1,41,1,9,1,70,1,18,1,10,1,5,1,23,1,6,1,5,1,40,1,39,1,47,1,26,1,39,1,19,1,55,1,32,1,1,1,16,3,2,1,61,1,72,1,5,1,84,1,46,1,9,1,3,1,38,1,38,1,23,1,31,1,10,2,10,1,5,1,38,1,9,1,3,1,5,1,5,1,36,1,2,1,2,1,23,1,54,1,31,1,52,1,28,1,62,1,2,1,17,1,7,1,3,1,12,1,31,1,43,1,1,1,38,1,3,1,20,1,47,1,30,1,27,1,3,1,29,1,4,1,4,1,2,1,5,1,9,1,3,1,16,1,5,1,3,1,26,1,8,1,18,1,2,1,26,1,13,1,18,1,9,2,38,1,3,1,9,1,4,2,55,1,10,1,6,1,23,2,40,1,17,2,20,1,29,1,4,1,1,1,17,2,9,1,4,1,31,1,32,1,57,1,1,1,3,1,10,1,7,1,40,1,42,1,6,2,19,1,8,1,3,1,18,1,19,1,20,1,2,1,8,1,8,1,8,1,2,1,5,3,13,1,9,1,5,1,18,1,36,1,35,1,43,1,17,2,20,1,51,1,4,1,18,1,17,1,6,1,45,2,9,1,5,1,19,1,2,1,7,1,1,1,15,2,9,1,4,1,33,1,7,1,11,1,2,1,7,1,13,1,10,1,18,1,4,1,7,1,44,1,29,1,3,1,8,1,13,2,23,1,13,1,20,1,5,1,28,1,26,1,14,1,6,1,2,1,10,1,8,1,9,1,1,1,28,1,16,1,30,1,25,1,21,1,4,2,42,1,27,1,11,1,16,1,3,1,33,1,7,1,43,1,19,1,2,1,7,1,4,1,24,1,14,1,32,1,15,1,19,2,64,1,2,2,8,1,21,1,44,1,10,1,13,1,28,1,16,1,4,1,31,1,10,2,14,1,23,1,7,1,1,1,46,1,2,2,16,1,1,1,16,1,16,1,5,1,22,1,52,1,15,1,10,1,48,1,11,1,21,1,22,1,4,1,1,1,35,1,5,1,12,1,1,1,26,1,18,1,12,1,7,1,1,1,15,1,29,1,1,1,31,1,4,1,12,1,10,1,10,1,9,1,18,1,9,1,5,1,20,1,9,1,10,1,26,1,18,1,68,2,31,1,5,1,7,1,15,1,8,1,11,1,2,1,3,1,9,1,3,1,6,1,27,1,1,1,1,1,1,1,3,1,6,1,14,1,4,1,3,1,1,1,4,1,2,1,35,1,21,1,48,1,11,1,8,1,14,1,14,1,2,1,7,1,6,1,25,1,9,1,44,2,11,1,46,1,2,1,29,1,48,1,3,1,13,1,17,1,6,1,15,1,10,1,1,1,3,1,5,1,3,1,1,1,30,1,4,1,24,1,35,2,27,1,73,1,6,1,14,1,9,1,31,1,8,1,14,1,30,1,40,1,41,1,3,1,33,1,6,1,44,1,18,1,63,1,51,1,7,1,22,1,7,1,2,1,17,1,28,1,21,1,20,1,1,2,94,2,29,1,50,1,31,1,9,1,6,1,1,2,9,1,11,1,13,1,4,1,14,1,3,1,4,1,3,1,14,1,14,2,15,1,41,1,19,1,27,1,1,1,3,1,21,1,6,1,4,1,1,1,43,1,49,2,8,1,4,1,45,1,3,1,4,1,10,2,13,1,14,1,9,1,3,1,29,1,28,1,25,1,26,1,7,1,7,1,26,1,18,1,1,1,39,1,5,1,17,1,7,1,35,1,34,1,15,1,61,1,52,1,10,1,52,1,19,1,5,1,27,1,10,1,18,1,3,1,21,1,81,1,5,1,46,2,2,1,9,1,7,1,4,1,46,1,24,1,13,1,22,1,12,1,45,1,19,1,13,1,38,1,32,1,19,1,6,1,4,1,13,1,12,1,26,1,17,1,11,1,14,1,18,1,26,1,13,1,53,1,7,1,8,1,23,1,9,1,4,1,1,1,15,1,17,1,5,1,31,1,68,1,15,1,72,1,8,1,10,1,9,1,2,1,28,1,9,1,2,1,31,1,4,1,22,1,9,1,2,1,3,1,12,1,32,1,10,1,9,1,1,1,20,1,5,1,1,1,17,1,11,1,4,1,7,1,3,1,60,1,20,1,6,1,4,1,26,1,23,2,17,1,1,1,12,1,8,1,1,1,40,1,41,1,14,1,49,1,11,1,27,1,5,1,14,1,17,1,4,1,54,1,47,1,14,1,23,1,2,1,4,1,29,1,16,1,7,1,7}},
};
vector<int>H(){
  int n, a, b;
  cin >> n >> a >> b;
  return {n, a ^ b};
}
void O(int task,T ans){
  int n = ans.first;
  vector<int> b = ans.second;
  for (int i = 0; i < b.size(); i++) {
    while (b[i]--) {
      cout << (i & 1) << '\n';
    }
  }
}
int main(){
auto V=H();
#define I(A,B,C) if(V[0]==A&&V[1]==B)O(C,M[C-1]);
I(30000,16253,1);
I(100000,55588,2);
I(7,6,3);
I(100,10,4);
I(100000,2155,5);
I(70000,75273,6);
I(12,0,7);
I(5,0,8);
I(4,0,9);
I(8000,6493,10);
}
