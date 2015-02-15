#include "mex.h" 
#include <ale_interface.hpp>
#include <class_handle.hpp>

using namespace std;

/* The mex function ale_mex to communicate with the ALE shared library interface
 * Input arguments:
 * 1 - keyword - {"new", "delete", "load", "reset", "act"} 
 * 2 - a class_handle for all keywords except "new"
 * 3 - for "load" this is the path to the ROM file, for "act" it is the number of the action to take
 * Output arguments:
 * If invoked with "delete" nothing
 * If invoked with "new" - the class_handle instance converted to Matlab matrix format
 * For all of other options:
 * 1 - the observation 
 * 2 - the reward
 * 3 - Flag
 * Flag values:
 * number of possible actions if invoked with "load"
 * -1 if game ended
 * 0 otherwise
 *
 * Alexander Botev
 * class_handle - http://www.mathworks.com/matlabcentral/fileexchange/38964-example-matlab-class-wrapper-for-a-c++-class
 */
void mexFunction(int nlhs, mxArray *plhs[], /* Output variables */
int nrhs, const mxArray *prhs[]) /* Input variables */
{
    char cmd[64];
	if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
		mexErrMsgTxt("ale_mex[10]: First input should be a command string less than 64 characters long.");
    
    // New
    if (!strcmp("new", cmd)) {
        // Check parameters
        if (nlhs != 1)
            mexErrMsgTxt("ale_mex[17]: Only one output expected.");
        // Return a handle to a new C++ instance
        plhs[0] = convertPtr2Mat<ALEInterface>(new ALEInterface);
        return;
    }
    
    // Check there is a second input, which should be the class instance handle
    if (nrhs < 2)
		mexErrMsgTxt("ale_mex[25]: Second input should be a class instance handle.");
    
    // Delete
    if (!strcmp("delete", cmd)) {
        // Destroy the C++ object
        destroyObject<ALEInterface>(prhs[1]);
        // Warn if other commands were ignored
        if (nlhs != 0 || nrhs != 2)
            mexWarnMsgTxt("ale_mex[3]: Delete - Unexpected arguments ignored.");
        return;
    }
    
    // Get the class instance pointer from the second input
    ALEInterface *ale = convertMat2Ptr<ALEInterface>(prhs[1]);
    
    // Warn if too many outputs
    
    if (nlhs > 3)
        mexErrMsgTxt("ale_mex[44]: Too many output arguments.");
    // Prepare reward and flag  output variables
    plhs[1] = mxCreateDoubleMatrix(1,1,mxREAL);
    double* reward = mxGetPr(plhs[1]);
    double* flag;
    if(strcmp("load", cmd)){
        plhs[2] = mxCreateDoubleMatrix(1,1,mxREAL);
        flag = mxGetPr(plhs[2]); 
    }
    
    // Load ROM file
    if (!strcmp("load", cmd)) {
        if (nrhs != 3)
            mexErrMsgTxt("ale_mex[42]: Load expects exactly 3 input arguments.");
        int buflen = mxGetNumberOfElements(prhs[2]) + 1;
        char* buf = (char *) mxCalloc(buflen, sizeof(char));
        mxGetString(prhs[2], buf, buflen);
        ale->loadROM(buf);
        *reward = 0;
        ActionVect acts = ale->getMinimalActionSet();
        mwSize s[2] = {acts.size(),1};
        plhs[2] = mxCreateCellArray(2,s);
        for(int i=0;i<acts.size();i++){
            mxSetCell(plhs[2], i, mxCreateString(action_to_string(acts[i]).c_str()));
            //cout << action_to_string(acts[i]) << endl;
        }
        //*actions = ale->getMinimalActionSet().size();
    }
    // Reset game
    else if (!strcmp("reset", cmd)){
        if (nrhs != 2)
            mexErrMsgTxt("ale_mex[42]: Reset expects exactly 2 input arguments.");
        *reward = 0;
        ale->reset_game();
    }
    // Act
    else if (!strcmp("act", cmd)){
        if (nrhs != 3)
            mexErrMsgTxt("ale_mex[42]: Act expects exactly 3 input arguments.");
        int action = (int)mxGetScalar(prhs[2]);
        *reward = ale->act(ale->getMinimalActionSet()[action-1]);
        if(ale->game_over())
            *flag = -1;
        else
            *flag = 0;
    }
    // Incorrect command
    else {
        mexErrMsgTxt("ale_mex[75]: Command not recognized.");
    }
    // Prepare screen output
    int h = ale->getScreen().height();
    int w = ale->getScreen().width();
    mwSize screenSize[2] = {h,w};
    plhs[0] = mxCreateNumericArray(2,screenSize,mxDOUBLE_CLASS , mxREAL);
    double* observation = mxGetPr(plhs[0]);
    pixel_t * pixels = ale->getScreen().getArray();
    for(int i=0;i<h;i++)
        for(int j=0;j<w;j++)
            observation[j*h+i] = pixels[i*w+j];
    return;
}