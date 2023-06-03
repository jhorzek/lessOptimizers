#ifndef ISTA_RIDGE_H
#define ISTA_RIDGE_H
#include "common_headers.h"

#include "proximalOperator.h"
#include "smoothPenalty.h"
#include "enet.h" // for definition of tuning parameters

namespace lessSEM{

class penaltyRidge: public smoothPenalty<tuningParametersEnet>{
public:
  
  double getValue(const arma::rowvec& parameterValues, 
                  const stringVector& parameterLabels,
                  const tuningParametersEnet& tuningParameters) override 
                  {
                    // if ridge is not used:
                    if(tuningParameters.alpha == 1) return(0.0);
                    
                    // else
                    double penalty = 0.0;
                    double lambda_i;
                    
                    for(unsigned int p = 0; p < parameterValues.n_elem; p ++){
                      
                      lambda_i = (1.0-tuningParameters.alpha) *
                        tuningParameters.lambda * 
                        tuningParameters.weights.at(p);
                      
                      penalty += lambda_i * std::pow(parameterValues.at(p), 2);
                    }
                    
                    return penalty;
                  }
  
  arma::rowvec getGradients(const arma::rowvec& parameterValues, 
                            const stringVector& parameterLabels,
                            const tuningParametersEnet& tuningParameters) override 
                            {
                              
                              arma::rowvec gradients(parameterValues.n_elem);
                              gradients.fill(0.0);
                              // if ridge is not used:
                              if(tuningParameters.alpha == 1) return(gradients);
                              
                              // else
                              
                              double lambda_i;
                              
                              for(unsigned int p = 0; p < parameterValues.n_elem; p ++){
                                
                                lambda_i = (1.0-tuningParameters.alpha) *
                                  tuningParameters.lambda * 
                                  tuningParameters.weights.at(p);
                                
                                gradients.at(p) = lambda_i * 
                                  2 * 
                                  parameterValues.at(p);
                              }
                              
                              return gradients;
                            } 
  
};
}
#endif
