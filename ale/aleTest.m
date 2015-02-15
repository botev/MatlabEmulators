%% ALE test script
% Runs a simple test to verify that the installation of ALE works
% Uses any game you specify in the path variable, please modify according
% to your system
%% Load ROM of the game and prepare variables
ale = ALE();
ng = randi(size(ale.availableGames,1));
fprintf('Playng "%s"\n...',ale.availableGames{ng});
[o,r,f] = ale.start(ale.availableGames{ng});
N = 1000;
os = zeros([size(o), N+1]);
os(:,:,1) = o;
rs = zeros(N+1,1);
%% Execute 1000 random actions and record the output and the runing time
tic;
for i=1:N
    if(f == -1)
        [o,r,f] = ale.reset();
    else
        [o,r,f] = ale.act(randi(ale.actionSize));
    end
    os(:,:,i+1) = o;
    rs(i+1) = r;
end
toc;
%% Plot the 251,501,751,1000 frames of the game
subplot(2,2,1);
imagesc(os(:,:,251));
axis image;
axis square;
subplot(2,2,2);
imagesc(os(:,:,501));
axis image;
axis square;
subplot(2,2,3);
imagesc(os(:,:,751));
axis image;
axis square;
subplot(2,2,4);
imagesc(os(:,:,1000));
axis image;
axis square;
