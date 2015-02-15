%% Set the paths of your machine apropriately 
pathToAle = '/media/hdd/data/Downloads/ale_0.4.4/ale_0_4/';
sdlFlag = 1;
ipath = ['-I' pathToAle 'src'];
lpath = ['-L' pathToAle];
%% Compile ale_mex
% Library flags:
% -lale
% If you compiled ALE with SDL additionally add:
%   -lSDL 
%   -lSDL_gfx
%   -lSDL_image
% mex('-v',ipath,lpath,'-lale', '-lSDL', '-lSDL_gfx', '-lSDL_image','ale_mex.cpp');
mex('-v',ipath,lpath,'-lale','ale_mex.cpp');