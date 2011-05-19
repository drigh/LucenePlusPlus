/////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2009-2011 Alan Wright. All rights reserved.
// Distributable under the terms of either the Apache License (Version 2.0)
// or the GNU Lesser General Public License.
/////////////////////////////////////////////////////////////////////////////

#ifndef _BOOLEANQUERY_H
#define _BOOLEANQUERY_H

#include "SimilarityDelegator.h"

namespace Lucene
{
    /// The Weight for BooleanQuery, used to normalize, score and explain these queries.
    class BooleanWeight : public Weight
    {
    public:
        BooleanWeight(BooleanQueryPtr query, SearcherPtr searcher, bool disableCoord);
        virtual ~BooleanWeight();
        
        LUCENE_CLASS(BooleanWeight);
    
    protected:
        BooleanQueryPtr query;
        
        /// The Similarity implementation.
        SimilarityPtr similarity;
        Collection<WeightPtr> weights;
        int32_t maxCoord; // num optional + num required
        bool disableCoord;
    
    public:
        virtual QueryPtr getQuery();
        virtual double getValue();
        virtual double sumOfSquaredWeights();
        virtual void normalize(double norm);
        virtual ExplanationPtr explain(IndexReaderPtr reader, int32_t doc);
        virtual ScorerPtr scorer(IndexReaderPtr reader, bool scoreDocsInOrder, bool topScorer);
        virtual bool scoresDocsOutOfOrder();
    };
    
    /// Disabled coord Similarity
    class SimilarityDisableCoord : public SimilarityDelegator
    {
    public:
        SimilarityDisableCoord(SimilarityPtr delegee);
        virtual ~SimilarityDisableCoord();
        
        LUCENE_CLASS(SimilarityDisableCoord);
    
    public:
        virtual double coord(int32_t overlap, int32_t maxOverlap);
    };
}

#endif