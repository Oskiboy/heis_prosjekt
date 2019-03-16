pipeline {
    agent { dockerfile true }
    environment {
        BUILD_OUTPUT = "project_build_binary.bin"
        TEST_OUTPUT = "test_binary.bin"
    }
    stages {
        stage('Initialization') {
            steps {
                sh """
                mkdir logs
                """
            }
        }
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
                    ./build/${TEST_OUTPUT} > logs/unit_tests.log
                else
                    echo "NO UNIT TESTS RUN." > logs/unit_tests.log
                fi
                '''
            }
        }
    }
    post {
        always {
            archiveArtifacts artifacts: "logs/*.log"
            sh '''
            ls
            echo "Starting clean"
            rm -rf build/ logs/
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
