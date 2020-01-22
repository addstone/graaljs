{
  local labsjdk8 = {name: 'oraclejdk', version: '8u241-jvmci-20.0-b01', platformspecific: true},

  local labsjdk_ce_11 = {name : 'labsjdk', version : 'ce-11.0.6+9-jvmci-20.0-b01', platformspecific: true},

  jdk8: {
    downloads+: {
      JAVA_HOME: labsjdk8,
      JDT: {name: 'ecj', version: '4.5.1', platformspecific: false},
    },
  },

  jdk11: {
    downloads+: {
      EXTRA_JAVA_HOMES: labsjdk8,
      JAVA_HOME: labsjdk_ce_11,
    },
  },

  deploy:      {targets+: ['deploy']},
  gate:        {targets+: ['gate']},
  postMerge:   {targets+: ['post-merge']},
  bench:       {targets+: ['bench', 'post-merge']},
  dailyBench:  {targets+: ['bench', 'daily']},
  weeklyBench: {targets+: ['bench', 'weekly']},
  weekly:      {targets+: ['weekly']},

  local python3 = {
    environment+: {
      MX_PYTHON_VERSION: "3",
    },
  },

  local common = python3 + {
    packages+: {
      'pip:pylint': '==1.9.3',
      'pip:ninja_syntax': '==1.7.2',
    },
    catch_files+: [
      'Graal diagnostic output saved in (?P<filename>.+.zip)',
      'npm-debug.log', // created on npm errors
    ],
    environment+: {
      GRAALVM_CHECK_EXPERIMENTAL_OPTIONS: "true",
    },
  },

  linux: common + {
    packages+: {
      'apache/ab': '==2.3',
      binutils: '==2.23.2',
      gcc: '==8.3.0',
      git: '>=1.8.3',
      maven: '==3.3.9',
      valgrind: '>=3.9.0',
    },
    capabilities+: ['linux', 'amd64'],
  },

  ol65: self.linux + {
    capabilities+: ['ol65'],
  },

  x52: self.linux + {
    capabilities+: ['no_frequency_scaling', 'tmpfs25g', 'x52'],
  },

  sparc: common + {
    capabilities: ['solaris', 'sparcv9'],
  },

  linux_aarch64: common + {
    capabilities+: ['linux', 'aarch64'],
    packages+: {
      gcc: '==8.3.0',
    }
  },

  darwin: common + {
    environment+: {
      // for compatibility with macOS El Capitan
      MACOSX_DEPLOYMENT_TARGET: '10.11',
    },
    capabilities: ['darwin', 'amd64'],
  },

  windows: common + {
    packages+: {
      'pip:ninja_syntax': '==1.7.2',
    },
    downloads+: {
      NASM: {name: 'nasm', version: '2.14.02', platformspecific: true},
    },
    environment+: {
      PATH: '$PATH;$NASM',
    },
    capabilities: ['windows', 'amd64'],
  },

  windows_vs2017: self.windows + {
    packages+: {
      'devkit:VS2017-15.5.5+1': '==0',
    },
    environment+: {
      GYP_MSVS_OVERRIDE_PATH: '$DEVKIT_ROOT',
      GYP_MSVS_VERSION: '2017',
    },
  },
}
