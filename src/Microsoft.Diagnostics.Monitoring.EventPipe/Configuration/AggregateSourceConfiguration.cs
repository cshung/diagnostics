// Licensed to the .NET Foundation under one or more agreements.
// The .NET Foundation licenses this file to you under the MIT license.

using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.Diagnostics.NETCore.Client;

namespace Microsoft.Diagnostics.Monitoring.EventPipe
{
    public sealed class AggregateSourceConfiguration : MonitoringSourceConfiguration
    {
        //! This is CoreCLR specific keywords for native ETW events (ending up in event pipe).
        //! The keywords below seems to correspond to:
        //!  GCKeyword                          (0x00000001)
        //!  LoaderKeyword                      (0x00000008)
        //!  JitKeyword                         (0x00000010)
        //!  NgenKeyword                        (0x00000020)
        //!  unused_keyword                     (0x00000100)
        //!  JittedMethodILToNativeMapKeyword   (0x00020000)
        //!  ThreadTransferKeyword              (0x80000000)
        internal const long defaultRundownKeyword = 0x80020139;

        private IList<MonitoringSourceConfiguration> _configurations;

        public AggregateSourceConfiguration(params MonitoringSourceConfiguration[] configurations)
        {
            _configurations = configurations;
        }

        public override IList<EventPipeProvider> GetProviders()
        {
            // CONSIDER: Might have to deduplicate providers and merge them together.
            return _configurations.SelectMany(c => c.GetProviders()).ToList();
        }

        public override bool RequestRundown
        {
            get => ComputeRundownKeyword() != 0;
            set => throw new NotSupportedException();
        }

        public override long? RundownKeyword
        {
            get
            {
                long keywords = ComputeRundownKeyword();
                return ((keywords == 0) || (keywords == defaultRundownKeyword)) ? null : keywords;
            }
            set => throw new NotSupportedException();
        }

        private long ComputeRundownKeyword()
        {
            long result = 0;
            foreach (MonitoringSourceConfiguration configurations in _configurations)
            {
                long rundownKeyword = defaultRundownKeyword;
                if (!configurations.RequestRundown)
                {
                    rundownKeyword = 0;
                }
                if (configurations.RundownKeyword.HasValue)
                {
                    rundownKeyword = configurations.RundownKeyword.Value;
                }
                result |= rundownKeyword;
            }
            return result;
        }
    }
}
