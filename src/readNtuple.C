#include <iostream>
#include <TFile.h>
#include <TTree.h>

// Define the structure to match the branches in the TTree
struct EdepData {
  double edep;
  int event_id;
  int cell_no;
};

void readNtuple(const char* filename) {
  // Create an instance of the structure to match the branches in the TTree
  EdepData data;

  // Open the ROOT file
  TFile* inputFile = TFile::Open(filename);

  if (!inputFile || inputFile->IsZombie()) {
    std::cerr << "Error: Unable to open ROOT file" << std::endl;
    return;
  }

  // Get the TTree named "Edep"
  TTree* edepTree = dynamic_cast<TTree*>(inputFile->Get("Edep"));

  if (!edepTree) {
    std::cerr << "Error: TTree 'Edep' not found in the ROOT file" << std::endl;
    inputFile->Close();
    return;
  }

  // Set branch addresses for the variables
  edepTree->SetBranchAddress("edep", &data.edep);
  edepTree->SetBranchAddress("event_id", &data.event_id);
  edepTree->SetBranchAddress("cell_no", &data.cell_no);

  // Get the number of entries in the TTree
  int numEntries = edepTree->GetEntries();

  // Loop over entries and print the data
  for (int entry = 0; entry < numEntries; ++entry) {
    edepTree->GetEntry(entry);

    // Print the data for each entry
    std::cout << "Entry: " << entry << ", edep: " << data.edep
              << ", event_id: " << data.event_id << ", cell_no: " << data.cell_no << std::endl;
  }

  // Close the ROOT file
  inputFile->Close();
}
