pipeline {
    agent { dockerfile true }
    environment {
        BUILD_OUTPUT = "project_build_binary.bin"
        TEST_OUTPUT = "test_binary.bin"
    }
    stages {
        stage('Build') {
            steps {
                sh '''
                echo "Starting build..."
                gcc --version
                
                sh build.sh
                '''
                sh 'echo "Build complete..."'
            }
        }
        stage('UnitTests') {
            steps {
                sh 'echo "Running Unit Tests..."'
                sh '''
                if [ -f build/${TEST_OUTPUT} ]; then
                    ./build/${TEST_OUTPUT} > build/unit_tests.log
                else
                    echo "NO UNIT TESTS RUN." > build/uinit_tests.log
                fi
                '''
            }
        }
    }
    post {
        always {
            archiveArtifacts artifacts: "build/unit_tests.log"
            sh '''
            echo "Starting clean"
            rm -rf build/
            '''
        }
        success {
            sh '''
            echo "All tests passed!"
            '''
        }
        failure {
            sh '''
            echo "Build failed!"
            '''
        }
    }
}
