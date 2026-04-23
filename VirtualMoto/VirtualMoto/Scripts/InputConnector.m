% This script facilitates Simscape connections

% Copyright 2022 The MathWorks, Inc.

function InputConnector(BlockName,flag,BlockType,BlockValue)

BlockFullPath = gcb;

TargetBlock = find_system(BlockFullPath,'SearchDepth',1,'LookUnderMasks','on','FollowLinks','on','Name',BlockName);

pos = get_param(TargetBlock,'position');
BType = get_param(TargetBlock,'BlockType');

switch flag
    case 'on'
        if ~strcmp(BType{1},'Inport')
            delete_block([BlockFullPath,'/',BlockName]);
            add_block('simulink/Sources/In1',[BlockFullPath,'/',BlockName]);
        end
    case 'off'
        switch BlockType
            case 'Ground'
                if ~strcmp(BType{1},'Ground')
                    delete_block([BlockFullPath,'/',BlockName]);
                    add_block('simulink/Sources/Ground',[BlockFullPath,'/',BlockName]);
                end
            case 'Constant'
                if ~strcmp(BType{1},'Constant')
                    delete_block([BlockFullPath,'/',BlockName]);
                    add_block('simulink/Sources/Constant',[BlockFullPath,'/',BlockName]);
                    set_param([BlockFullPath,'/',BlockName],'Value',BlockValue);
                end
        end
end

set_param([BlockFullPath,'/',BlockName],'position',pos{1});

end
