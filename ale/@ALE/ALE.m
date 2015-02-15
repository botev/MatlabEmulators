classdef ALE < AbstractEmulator
    % ALE - Agent Learning Enviornment interface trough MATLAB
    % Methods:
    % loadROM - loads the ROM file from the path spesified in to the
    % emulator 
    % reset - resets the current make and starts a new one from the same
    % ROM file
    % act - makes a single action from the currently possible actions
    %
    % Each one returns a triple [o,r,f] of observation, reward and flag
    % The flag is -1 if the game ends, 0 otherwise and the number of
    % possible actions when the loadROM is invoked.
    
    properties (SetAccess = private, Hidden = true)
        % Handle to the underlying C++ ALE interface
        aleHandle; 
        romsPath;
    end
    properties 
        availableGames
        actionSize
        actionNames
    end
    
    methods
        % Constructor
        function this = ALE()
            this.aleHandle = ale_mex('new');
            this.actionSize = 0;
            this.romsPath = mfilename('fullpath');
            this.romsPath = [this.romsPath(1:strfind(this.romsPath,'/@ALE')), 'roms/'];
            files = dir(this.romsPath);
            c = 2;
            for i=3:size(files,1)
                if(strcmp('state',files(i).name));
                    c = 3;
                else
                    this.availableGames{i-c,1} = files(i).name(1:end-4);
                end
            end
        end
        % Destructor
        function delete(this)
            ale_mex('delete', this.aleHandle);
        end
        % Load new ROM
        function [o,r,f] = start(this,game)
            if(~exist([this.romsPath, game, '.bin'],'file'))
                error('File does not exist.');
            end
            [o,r,this.actionNames] = ale_mex('load', this.aleHandle, [this.romsPath, game, '.bin']);
            this.actionSize = size(this.actionNames,1);
            f = this.actionSize;
        end
        % Reset the game
        function [o,r,f] = reset(this)
            if(this.actionSize == 0)
                error('File does not exist.');
            end
            [o,r,f] = ale_mex('reset', this.aleHandle);
        end
        % Make an action
        function [o,r,f] = act(this,action)
            if(action < 0 || action > this.actionSize)
                error('Action is not in the possible set.');
            end
            [o,r,f] = ale_mex('act', this.aleHandle, action);
        end
    end
    
end

